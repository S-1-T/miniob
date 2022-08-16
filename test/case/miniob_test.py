# -*- coding: UTF-8 -*-

from genericpath import exists
import os
import json
import http.client
import sys
import logging
import subprocess
import socket
import select
import time
import shutil
#import timeout_decorator
from enum import Enum
#import eventlet
#from timeout_decorator import TimeoutError
try:
  from optparse import OptionParser
except:
  print("cannot load optparse module")
  exit(1)

"""
为OceanBase 大赛测试平台设计的自动化测试程序
测试流程：
获取源码 -> 
编译源码 ->
获取测试用例文件 ->
启动observer ->
执行测试用例 ->
对比执行结果与预先设置的结果文件

- 获取源码的方式：支持通过git获取，也可以指定源码的zip压缩包路径
- 编译源码：可以指定编译的cmake和make参数。也可以跳过这个步骤。
- 测试用例文件：测试用例文件都以.test结尾，当前放在test目录下，分为necessary和option(后续可以考虑删除)
- 测试结果文件：预先设置的结果文件，以.result结尾，放在result目录下
- 启动observer: 启动observer，使用unix socket，这样可以每个observer使用自己的socket文件
- 执行测试用例：测试用例文件中，每行都是一个命令。命令可以是SQL语句，也可以是预先定义的命令，比如 echo，sort等
- 评分文件：当前为 case-scores.json 文件，内容为json格式，描述每个case的分值
- 测试：使用参数直接连接已经启动的observer

TODO list
- 控制所有用例一共执行的时长
- 简化部分配置项，已知：增加测试base-dir目录，在base-dir下查找test/result/case-scores.json文件

How to use:
 使用git下载代码然后测试
python3 miniob_test.py \
        --test-case-dir=./test  \
        --test-case-scores=case-scores.json \
        --test-result-dir=result \
        --test-result-tmp-dir=./result_tmp \
        --use-unix-socket \
        --git-repo=https://github.com/oceanbase/miniob.git \
        --git-branch=main \
        --code-type=git \
        --target-dir=./miniob \
        --log=stdout \
        --compile-make-args=-j4
"""


class TimeoutException(BaseException):
  def __init__(self, value="Timed Out"):
    self.value = value

  def __str__(self):
    return repr(self.value)

class Result(Enum):
  true = True
  false = False
  timeout = 0

class GlobalConfig:
  default_encoding = "UTF-8"
  debug = False
  source_code_build_path_name = "build"

def __get_source_path(target_dir: str):
  return target_dir + '/miniob'

def __get_project_path(target_dir: str):
  return __get_source_path(target_dir)

def __get_data_path(target_dir: str):
  return target_dir + '/data'

def __get_result_path(target_dir: str):
  return target_dir + '/result'

def __get_build_path(target_dir: str):
  return target_dir + '/' + GlobalConfig.source_code_build_path_name

class ResultWriter:
  '''
  写数据到指定文件，当前用于输出测试结果
  '''

  def __init__(self, file):
    self.__file = file

  def __exit__(self, exc_type, exc_value, exc_tb):
    self.close()
  
  def close(self):
    if self.__file is not None:
      self.__file.close()
      self.__file = None

  def write(self, arg: str):
    self.__file.write(bytes(arg.upper(), GlobalConfig.default_encoding))

  def write_line(self, arg: str):
    self.write(str(arg).upper())
    self.write('\n')

class MiniObServer:
  '''
  用来控制miniob的服务器程序。负责程序的启停和环境的初始化和清理工作
  '''

  def __init__(self, base_dir: str, data_dir: str, config_file: str, server_port: int, server_socket: str, clean_data_dir: bool):
    self.__check_base_dir(base_dir)
    self.__check_data_dir(data_dir, clean_data_dir)

    self.__base_dir = base_dir
    self.__data_dir = data_dir

    if config_file == None:
      config_file = self.__default_config(base_dir)
    self.__check_config(config_file)
    self.__config = config_file
    self.__server_port = server_port
    self.__server_socket = server_socket.strip()

    self.__process = None

  def __enter__(self):
    return self

  def __exit__(self, exc_type, exc_value, exc_tb):
    if self.__process is not None:
      self.stop_server()
      self.clean()
      self.__process = None

  def __observer_path(self, base_dir: str):
    '''
    observer程序所在路径
    '''
    return base_dir + "/bin/observer"

  def __default_config(self, base_dir: str):
    return base_dir + "/etc/observer.ini"

  def __check_base_dir(self, base_dir: str):
    if not(os.path.isdir(base_dir)):
      raise(Exception("failed to check base directory. " + base_dir + " is not a directory"))
    
    observer_path = self.__observer_path(base_dir)
    if not(os.path.isfile(observer_path)):
      raise(Exception("observer not exists: " + observer_path))

  def __check_data_dir(self, data_dir: str, clean_data_dir: bool):
    if os.path.exists(data_dir) and clean_data_dir:
      shutil.rmtree(data_dir)

    os.makedirs(data_dir, exist_ok=True)
    if not(os.path.isdir(data_dir)):
      raise(Exception(data_dir + " is not a directory or failed to create"))
    
    # results = os.listdir(data_dir)
    # if len(results) != 0:
    #   raise(Exception(data_dir + " is not empty"))

  def __check_config(self, config_file: str):
    if not(os.path.isfile(config_file)):
      raise(Exception("config file does not exists: " + config_file))

  def init_server(self):
    logging.info("miniob-server inited")
    # do nothing now

  def start_server(self):
    '''
    启动服务端程序，并使用探测端口的方式检测程序是否正常启动
    调试模式如果可以使用调试器启动程序就好了
    '''

    if self.__process != None:
      logging.warn("Server has already been started")
      return False

    time_begin = time.time()
    logging.debug("use '%s' as observer work path", os.getcwd())
    observer_command = [self.__observer_path(self.__base_dir), '-f', self.__config]
    if len(self.__server_socket) > 0:
      observer_command.append('-s')
      observer_command.append(self.__server_socket)
    else:
      observer_command.append('-p')
      observer_command.append(str(self.__server_port))

    process = subprocess.Popen(observer_command, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, cwd=self.__data_dir)
    return_code = process.poll()
    if return_code != None:
      logging.error("Failed to start observer, exit with code %d", return_code)
      return False
    
    logging.info('start subprocess with pid=%d', process.pid)
    #os.setpgid(process.pid, GlobalConfig.group_id)

    self.__process = process
    time.sleep(0.2)
    if not self.__wait_server_started(10):
      time_span = time.time() - time_begin
      logging.error("Failed to start server in %f seconds", time_span)
      return False

    time_span = time.time() - time_begin
    logging.info("miniob-server started in %f seconds", time_span)
    return True

  def stop_server(self):
    if self.__process == None:
      logging.warning("Server has not been started")
      return True

    self.__process.terminate()
    return_code = -1
    try:
      return_code = self.__process.wait(10)
      if return_code is None:
        self.__process.kill()
        logging.warning("Failed to stop server: %s", self.__base_dir)
        return False
    except Exception as ex:
      self.__process.kill()
      logging.warning("wait server exit timedout: %s", self.__base_dir)
      return False

    logging.info("miniob-server exit with code %d. pid=%s", return_code, str(self.__process.pid))
    return True

  def clean(self):
    ''' 
    清理数据目录（如果没有配置调试模式）
    调试模式可能需要查看服务器程序运行的日志
    '''

    if GlobalConfig.debug is False:
      shutil.rmtree(self.__data_dir)
    logging.info("miniob-server cleaned")

  def __check_unix_socket_server(self):
    with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as s:
      errno = s.connect_ex(self.__server_socket)
      if errno == 0:
        return True
      else:
        logging.debug("Failed to connect to server. err=%d:%s", errno, os.strerror(errno))
        return False

  def __check_tcp_socket_server(self):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
      errno = s.connect_ex(('127.0.0.1', self.__server_port))
      if errno == 0:
        return True
      else:
        logging.debug("Failed to connect to server. err=%d:%s", errno, os.strerror(errno))
        return False

  def __wait_server_started(self, timeout_seconds: int):
    deadline = time.time() + timeout_seconds

    while time.time() <= deadline:
      result = False
      if len(self.__server_socket) > 0:
        result = self.__check_unix_socket_server()
      else:
        result = self.__check_tcp_socket_server()
      if result:
        return result
      time.sleep(0.5)

    return False

class MiniObClient:
  '''
  测试客户端。使用TCP连接，向服务器发送命令并反馈结果
  '''

  def __init__(self, server_port: int, server_socket: str, time_limit:int = 10):
    if (server_port < 0 or server_port > 65535) and server_socket is None:
      raise(Exception("Invalid server port: " + str(server_port)))

    self.__server_port = server_port
    self.__server_socket = server_socket.strip()
    self.__socket = None
    self.__buffer_size = 8192

    sock = None
    if len(self.__server_socket) > 0:
      sock = self.__init_unix_socket(self.__server_socket)
    else:
      sock = self.__init_tcp_socket(self.__server_port)

    self.__socket = sock
    if sock != None:
      self.__socket.setblocking(False)
      #self.__socket.settimeout(time_limit) # do not work

      self.__time_limit = time_limit
      self.__poller = select.poll()
      self.__poller.register(self.__socket, select.POLLIN | select.POLLPRI | select.POLLHUP | select.POLLERR)

  def __init_tcp_socket(self, server_port:int):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    errno = s.connect_ex(('127.0.0.1', server_port))
    if errno != 0:
      logging.error("Failed to connect to server with port %d. errno=%d:%s", 
                    server_port, errno, os.strerror(errno))
      s = None
    return s

  def __init_unix_socket(self, server_socket: str):
    sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    errno = sock.connect_ex(server_socket)
    if errno != 0:
      logging.error("Failed to connect to server with address '%s'. errno=%d:%s", 
                    server_socket, errno, os.strerror(errno))
      sock = None
    return sock

  def is_valid(self):
    return self.__socket is not None

  def __recv_response(self):
    result = ''
    
    while True:
      events = self.__poller.poll(self.__time_limit * 1000)
      if len(events) == 0:
        raise Exception('Poll timeout after %d second(s)' % self.__time_limit)

      (_, event) = events[0]
      if event & (select.POLLHUP | select.POLLERR):
        msg = "Failed to receive from server. poll return POLLHUP(%s) or POLLERR(%s)" % ( str(event & select.POLLHUP), str(event & select.POLLERR))
        logging.info(msg)
        raise Exception(msg)
      
      data = self.__socket.recv(self.__buffer_size)
      if len(data) > 0:
        result_tmp = data.decode(encoding= GlobalConfig.default_encoding)
        logging.debug("receive from server[size=%d]: '%s'", len(data), result_tmp)
        if data[len(data) - 1] == 0:
          result += result_tmp[0:-2]
          return result.strip() + '\n'
        else:
          result += result_tmp # TODO 返回数据量比较大的时候，python可能会hang住
                               # 可以考虑返回列表
      else:
        logging.info("receive from server error. result len=%d", len(data))
        raise Exception("receive return error. the connection may be closed")
          

  def run_sql(self, sql: str):
    try:
      data = str.encode(sql, GlobalConfig.default_encoding)
      self.__socket.sendall(data)
      self.__socket.sendall(b'\0')
      logging.debug("send command to server(size=%d) '%s'", len(data) + 1, sql)
      result = self.__recv_response()
      logging.debug("receive result from server '%s'", result)
      return True, result
    except Exception as ex:
      logging.error("Failed to send message to server: '%s'", str(ex))
      return False, None

  def close(self):
    if self.__socket is not None:
      self.__socket.close()
      self.__socket = None

class CommandRunner:
  __default_client_name = "default"
  __command_prefix = "--"
  __comment_prefix = "#"

  def __init__(self, result_writer: ResultWriter, server_port: int, unix_socket: str):
    self.__result_writer = result_writer
    self.__clients = {}

    # create default client
    default_client = MiniObClient(server_port, unix_socket)
    if not( default_client.is_valid()):
      self.__is_valid = False
    else:
      self.__is_valid = True
      self.__clients[self.__default_client_name] = default_client

    self.__current_client = default_client
    self.__server_port = server_port
    self.__unix_socket = unix_socket

  def is_valid(self):
    return self.__is_valid

  def __enter__(self):
    return self
  
  def __exit__(self, exc_type, exc_value, exc_tb):
    self.close()

  def close(self):
    for client in self.__clients.values():
      client.close()
    self.__clients.clear()
    self.__current_client = None

  def run_connection(self, name: str):
    '''
    切换当前连接
    '''

    client = self.__clients[name]
    if client == None:
      logging.error("No such client named %s", name)
      return False

    self.__current_client = client
    return True

  def run_connect(self, name: str):
    '''
    创建一个连接。每个连接有一个名字，可以使用使用connection name来切换当前的连接
    '''
    name = name.strip()
    if len(name) == 0:
      logging.error("Found empty client name")
      return False

    client = self.__clients[name]
    if client != None:
      logging.error("Client with name %s already exists", name)
      return False

    client = MiniObClient(self.__server_port, self.__unix_socket)
    if not(client.is_valid()):
      logging.error("Failed to create client with name: %s", name)
      return False

    self.__clients[name] = client
    return True

  def run_echo(self, arg: str):
    '''
    echo 命令。参数可以是#开头的注释，这里不关心
    '''

    self.__result_writer.write_line(arg)
    return True

  def run_sql(self, sql):
    self.__result_writer.write_line(sql)
    result, data = self.__current_client.run_sql(sql)
    if result is False:
      return False
    self.__result_writer.write(data)
    return True

  def run_sort(self, sql):
    self.__result_writer.write_line(sql)
    result, data = self.__current_client.run_sql(sql)
    if result is False:
      return False
    data_l = data.strip().split('\n')
    data_l.sort()
    data = '\n'.join(data_l) + '\n'
    self.__result_writer.write(data)
    return result

  def run_command(self, command_line: str):
    '''
    执行一条命令。命令的参数使用空格分开, 第一个字符串是命令类型
    '''
    command_line = command_line[len(self.__command_prefix) : ]
    command_line = command_line.lstrip()
    args = command_line.split(' ', 1)
    command = args[0]

    command_arg = ''
    if len(args) > 1:
      command_arg = args[1]

    result = True
    if 'echo' == command:
      result = self.run_echo(command_arg)
    elif 'connect' == command:
      result = self.run_connect(command_arg)
    elif 'connection' == command:
      result = self.run_connection(command_arg)
    elif 'sort' == command:
      result = self.run_sort(command_arg)
    else:
      logging.error("No such command %s", command)
      result = False

    return result
    
  def run_anything(self, argline: str):
    argline = argline.strip()
    if len(argline) == 0:
      self.__result_writer.write_line('') # 读取到一个空行，也写入一个空行
      return True
    
    if argline.startswith(self.__comment_prefix):
      return True
    
    if argline.startswith(self.__command_prefix):
      return self.run_command(argline)

    return self.run_sql(argline)

class TestCase:

  def __init__(self, is_necessary: bool, score: int):
    self.__name = ''
    self.__necessary = is_necessary
    self.__score = score
    self.__lines = []

  def init_with_file(self, name, filename):
    self.__name = name
    with open(filename, mode='r') as f:
      self.__lines = f.readlines()
    return True

  def init_with_content(self, name, lines):
    self.__name = name
    self.__lines = lines
    return True

  def command_lines(self):
    return self.__lines

  def get_name(self):
    return self.__name

  def is_necessary(self):
    return self.__necessary

  def get_score(self):
    return self.__score

  def result_file(self, base_dir):
    subdir = ''
    #if self.__necessary:
    #  subdir = self.NECESSARY_DIR
    #else:
    #  subdir = self.OPTION_DIR
    return base_dir + "/" + subdir + "/" + self.__name + ".result"

  def tmp_result_file(self, base_dir):
    result_file = self.result_file(base_dir)
    return result_file + '.tmp'

class TestCaseLister:

  def __init__(self, suffix = None):
    if suffix != None:
      self.__suffix = suffix
    else:
      self.__suffix = ".test"

  def list_by_test_score_file(self, test_scores, test_case_file_dir: str):
    '''
    从test-score文件中加载所有测试用例
    '''
    test_cases = []
    test_score_infos = test_scores.get_all()
    for case_name, test_score in test_score_infos.items():
      test_case = TestCase(test_score.is_necessary(), test_score.score())
      test_case_file = test_case_file_dir + '/' + case_name + self.__suffix
      test_case.init_with_file(case_name, test_case_file)
      test_cases.append(test_case)

    return test_cases

  def list_directory(self, base_dir : str, is_necessary: bool):
    test_case_files = []

    is_dir = os.path.isdir(base_dir)
    if False == is_dir:
      raise(Exception("Failed to list directory while getting test cases. " + base_dir + " is not a directory"))

    files = os.listdir(base_dir)
    for filename in files:
      logging.debug("find file %s", filename)
      if filename.startswith('.'):
        continue

      full_path = base_dir + "/" + filename
      is_file = os.path.isfile(full_path)
      if False == is_file:
        continue
      if filename.endswith(self.__suffix):
        test_case_files.append(filename)

    test_cases = []
    for test_case_file in test_case_files:
      full_path = base_dir + "/" + test_case_file
      test_case_name = test_case_file[0 : -len(self.__suffix)]
      test_case = TestCase(is_necessary, 0)
      test_case.init_with_file(test_case_name, full_path)
      test_cases.append(test_case)
      logging.debug("got a test case file %s", str(test_case_file))

    return test_cases

  def list_all(self, base_dir, test_names):
    is_dir = os.path.isdir(base_dir)
    if False == is_dir:
      raise("Failed to list all test cases. " + base_dir + " is not a directory")

    test_cases = []
    for test_name in test_names:
      full_path = base_dir + "/" + test_name + self.__suffix
      if not(os.path.isfile(full_path)):
        raise(Exception(full_path + " is not a file"))
      
      test_case = TestCase(False, 0)
      test_case.init_with_file(test_name, full_path)
      test_cases.append(test_case)
      logging.debug("got a test case %s", test_case)

    return test_cases

class TestScore:
  def __init__(self, is_necessary: bool, score: int):
    self.__necessary = is_necessary
    self.__score = score

  def is_necessary(self):
    return self.__necessary
  def score(self):
    return self.__score

class TestScores:
  def __init__(self):
    self.__scores = {}
    self.__is_valid = False

  def is_valid(self):
    return self.__is_valid

  def init_file(self, fp):
    score_infos = json.load(fp)
    self.__init(score_infos)

  def init_content(self, content: str):
    score_infos = json.loads(content)
    self.__init(score_infos)

  def __init(self, score_info_dict: dict):
    scores = {}
    for name, score_info in score_info_dict.items():
      scores[name] = TestScore(score_info['necessary'], score_info['score'])

    self.__scores = scores
    self.__is_valid = True
  
  def is_necessary(self, name):
    if name in self.__scores.keys():
      return self.__scores[name].is_necessary()

    return None
  
  def acquire_score(self, name):
    if name in self.__scores.keys():
      return self.__scores[name].score()

    return None

  def get_all(self):
    return self.__scores

class EvalResult:
  def __init__(self):
    self.__message = []
    self.__necessary_score = 0
    self.__option_score = 0
    self.__status = -1
    
  def clear_message(self):
    self.__message = []
    
  def append_message(self, message):
    self.__message.append(message)
    
  def get_message(self):
    return "\n".join(self.__message)
  
  def add_necessary_score(self, score: int):
    self.__necessary_score += score

  def add_option_score(self, score: int):
    self.__option_score += score

  def clear_option_score(self):
    self.__option_score = 0

  def clear_score(self):
    self.__option_score = 0
    self.__necessary_score = 0
    
  def get_score(self):
    return self.__necessary_score + self.__option_score
  
  def set_cost(self):
    self.__status = 0
    
  def set_no_cost(self):
    self.__status = -1
    
  def get_status(self):
    return self.__status
  
  def is_success(self):
    return self.__status == 0

  def to_json_string(self):
    json_dict = {}
    json_dict['score'] = self.get_score()
    json_dict['message'] = self.get_message()

    json_encoder = json.encoder.JSONEncoder()
    json_encoder.item_separator = ','
    json_encoder.key_separator = ':'
    return json_encoder.encode(json_dict)
  
class TestSuite:

  def __init__(self):
    self.__report_only = False # 本次测试为了获取测试结果，不是为了校验结果
    self.__test_case_base_dir = "./test"
    self.__test_result_base_dir = "./result"
    self.__test_result_tmp_dir = "./result/tmp" # 生成的结果存放的临时目录
    self.__db_server_base_dir = None
    self.__db_data_dir = None
    self.__db_config = None
    self.__server_port = 0
    self.__use_unix_socket = False # 如果指定unix socket，那么就不再使用TCP连接
    self.__need_start_server = True
    self.__test_names = None # 如果指定测试哪些Case，就不再遍历所有的cases
    self.__miniob_server = None
    self.__test_case_scores = TestScores()
  
  def set_test_names(self, tests):
    self.__test_names = tests

  def set_test_case_base_dir(self, test_case_base_dir):
    self.__test_case_base_dir = test_case_base_dir
  
  def set_test_result_base_dir(self, test_result_base_dir):
    self.__test_result_base_dir = test_result_base_dir

  def set_test_result_tmp_dir(self, test_result_tmp_dir: str):
    self.__test_result_tmp_dir = test_result_tmp_dir
    os.makedirs(test_result_tmp_dir, exist_ok=True)
    if not(os.path.isdir(test_result_tmp_dir)):
      raise(Exception("Failed to set test result temp directory. " + test_result_tmp_dir + " is not a directory or failed to create"))
  
  def set_test_case_scores(self, scores_path: str):
    with open(scores_path) as fp:
      self.__test_case_scores.init_file(fp)

  def set_db_server_base_dir(self, db_server_base_dir):
    self.__db_server_base_dir = db_server_base_dir

  def set_db_data_dir(self, db_data_dir):
    self.__db_data_dir = db_data_dir

  def set_db_config(self, db_config):
    self.__db_config = db_config

  def set_server_port(self, server_port):
    self.__server_port = server_port

  def set_use_unix_socket(self, use_unix_socket: bool):
    self.__use_unix_socket = use_unix_socket

  def donot_need_start_server(self):
    self.__need_start_server = False

  def set_report_only(self, report_only):
    self.__report_only = report_only

  def __compare_files(self, file1, file2):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
      lines1 = f1.readlines()
      lines2 = f2.readlines()
      if len(lines1) != len(lines2):
        return False

      line_num = len(lines1)
      for i in range(line_num):
        if lines1[i].upper() != lines2[i].upper():
          logging.info('file1=%s, file2=%s, line1=%s, line2=%s', file1, file2, lines1[i], lines2[i])
          return False
      return True

  def run_case(self, test_case, timeout=20):
    # eventlet.monkey_patch()
    #@timeout_decorator.timeout(timeout)
    #def decorator():
    try:
      #with eventlet.Timeout(timeout):
      ret = self.__run_case(test_case)
      if ret:
        return Result.true
      else:
        return Result.false
    except TimeoutException as ex:
      return Result.timeout

    # try:
    #   ret = decorator()
    #   if ret:
    #     return Result.true
    #   return Result.false
    # except TimeoutError:
    #   return Result.timeout

  def __run_case(self, test_case: TestCase):
    result_tmp_file_name = test_case.tmp_result_file(self.__test_result_tmp_dir)

    unix_socket = ''
    if self.__use_unix_socket:
      unix_socket = self.__get_unix_socket_address()

    with open(result_tmp_file_name, mode='wb') as result_file:
      result_writer = ResultWriter(result_file)

      with CommandRunner(result_writer, self.__server_port, unix_socket) as command_runner:
        if command_runner.is_valid() == False:
          return False

        for command_line in test_case.command_lines():
          result = command_runner.run_anything(command_line)
          if result is False:
            logging.error("Failed to run command %s in case %s", command_line, test_case.get_name())
            return result

    result_file_name = test_case.result_file(self.__test_result_base_dir)
    if self.__report_only:
      os.rename(result_tmp_file_name, result_file_name)
      return True
    else:
      result = self.__compare_files(result_tmp_file_name, result_file_name)
      if not GlobalConfig.debug:
        #os.remove(result_tmp_file_name)
        pass
      return result

  def __get_unix_socket_address(self):
    return self.__db_data_dir + '/miniob.sock'

  def __get_all_test_cases(self):
    test_case_lister = TestCaseLister()
    test_cases = []
    if self.__test_case_scores.is_valid():
      test_cases = test_case_lister.list_by_test_score_file(self.__test_case_scores, self.__test_case_base_dir)
    else:
      test_cases = test_case_lister.list_directory(self.__test_case_base_dir)

    if self.__test_names is None: # 没有指定测试哪个case
      return test_cases

    # 指定了测试case，就从中捞出来
    # 找出指定了要测试某个case，但是没有发现
    test_case_result = []
    for case_name in self.__test_names:
      found = False
      for test_case in test_cases:
        if test_case.get_name() == case_name:
          test_case_result.append(test_case)
          logging.debug("got case: " + case_name)
          found = True
      if found == False:
        logging.error("No such test case with name '%s'" % case_name)
        return []

    return test_case_result

  def run(self, eval_result: EvalResult):

    # 找出所有需要测试Case
    test_cases = self.__get_all_test_cases()
    
    if test_cases is None or len(test_cases) == 0:
      logging.info("Cannot find any test cases")
      return True

    logging.info("Starting observer server")

    # 测试每个Case
    success_count = 0
    failure_count = 0
    timeout_count = 0
    necessary_all_passed = True
    for test_case in test_cases:
      try:
        # 每个case都清理并重启一下服务端，这样可以方式某个case core之后，还能测试其它case
        self.__clean_server_if_need()

        result = self.__start_server_if_need(True)
        if result is False:
          eval_result.append_message('Failed to start server.')
          eval_result.set_no_cost()
          return False

        logging.info(test_case.get_name() + " starting ...")
        result = self.run_case(test_case)

        if result is Result.true:
          logging.info("Case passed: %s", test_case.get_name())
          success_count += 1
          if test_case.is_necessary():
            eval_result.add_necessary_score(test_case.get_score())
          else:
            eval_result.add_option_score(test_case.get_score())
          eval_result.append_message("%s is success" % test_case.get_name())
        else: 
          if self.__test_case_scores.is_necessary(test_case.get_name()):
            necessary_all_passed = False

          if result is Result.false:
            logging.info("Case failed: %s", test_case.get_name())
            failure_count += 1
            eval_result.append_message("%s is error" % test_case.get_name())
          else:
            logging.info("Case timeout: %s", test_case.get_name())
            timeout_count += 1
            eval_result.append_message("%s is timeout" % test_case.get_name())
      except Exception as ex:
        logging.error("Failed to run case %s", test_case.get_name())
        self.__clean_server_if_need()
        raise ex

    logging.info("All done. %d passed, %d failed, %d timeout", success_count, failure_count, timeout_count)
    logging.debug(eval_result.get_message())
    if necessary_all_passed is False:
      eval_result.clear_option_score()
    eval_result.set_cost()
    self.__clean_server_if_need()
    return True

  def __start_server_if_need(self, clean_data_dir: bool):
    if self.__miniob_server is not None:
      return True

    if self.__need_start_server:
      unix_socket = ''
      if self.__use_unix_socket:
        unix_socket = self.__get_unix_socket_address()

      miniob_server = MiniObServer(self.__db_server_base_dir, self.__db_data_dir, 
          self.__db_config, self.__server_port, unix_socket, clean_data_dir)
      miniob_server.init_server()
      result = miniob_server.start_server()
      if result is False:
        logging.error("Failed to start db server")
        miniob_server.stop_server()
        miniob_server.clean()
        return False
      self.__miniob_server = miniob_server

    return True

  def __clean_server_if_need(self):
    if self.__miniob_server is not None:
      self.__miniob_server.stop_server()
      # 不再清理掉中间结果。如果从解压代码开始，那么执行的中间结果不需要再清理，所有的数据都在临时目录
      # self.__miniob_server.clean() 
      self.__miniob_server = None

def __init_options():
  options_parser = OptionParser()
  # 是否仅仅生成结果，而不对结果做校验。一般在新生成一个case时使用
  options_parser.add_option('', '--report-only', action='store_true', dest='report_only', default=False, 
                            help='just report the result')
  # 测试case文件存放的目录
  options_parser.add_option('', '--test-case-dir', action='store', type='string', dest='test_case_base_dir', default='test',
                            help='the directory that contains the test files')
  # 测试case文件存放的目录
  options_parser.add_option('', '--test-case-scores', action='store', type='string', dest='test_case_scores', default='score.json',
                            help='a json file that records score of the test cases')
  # 测试结果文件存放目录
  options_parser.add_option('', '--test-result-dir', action='store', type='string', dest='test_result_base_dir', default='result',
                            help='the directory that contains the test result files')
  # 生成的测试结果文件临时目录
  options_parser.add_option('', '--test-result-tmp-dir', action='store', type='string', dest='test_result_tmp_dir', default='result/tmp',
                            help='the directory that contains the generated test result files')

  # 测试哪些用例。不指定就会扫描test-case-dir目录下面的所有测试用例。指定的话，就从test-case-dir目录下面按照名字找
  options_parser.add_option('', '--test-cases', action='store', type='string', dest='test_cases', 
                            help='test cases. If none, we will iterate the test case directory. Split with \',\' if more than one')

  # 测试时服务器程序基础路径，下面包含bin/observer执行主程序和etc/observer.ini配置文件
  options_parser.add_option('', '--db-base-dir', action='store', type='string', dest='db_base_dir',
                            help='the directory of miniob database which db-base-dir/bin contains the binary executor file')
  
  # 测试时服务器程序的数据文件存放目录
  options_parser.add_option('', '--db-data-dir', action='store', type='string', dest='db_data_dir', default='miniob_data_test',
                            help='the directory of miniob database\'s data for test')

  # 服务程序配置文件
  options_parser.add_option('', '--db-config', action='store', type='string', dest='db_config',
                            help='the configuration of db for test. default is base_dir/etc/observer.ini')
  # 服务程序端口号，客户端也使用这个端口连接服务器。目前还不具备通过配置文件解析端口配置的能力
  options_parser.add_option('', '--server-port', action='store', type='int', dest='server_port', default=6789,
                            help='the server port. should be the same with the value in the config')
  options_parser.add_option('', '--use-unix-socket', action='store_true', dest='use_unix_socket',
                            help='If true, server-port will be ignored and will use a random address socket.')
  
  # 可以手动启动服务端程序，然后添加这个选项，就不会再启动服务器程序。一般调试时使用
  options_parser.add_option('', '--server-started', action='store_true', dest='server_started', default=False,
                            help='Whether the server is already started. If true, we will not start the server')

  # 测试过程中生成的日志存放的文件。使用stdout/stderr输出到控制台
  options_parser.add_option('', '--log', action='store', type='string', dest='log_file', default='miniob-test.log',
                            help='log file. stdout=standard output and stderr=standard error')
  # 是否启动调试模式。调试模式不会清理服务器的数据目录
  options_parser.add_option('-d', '--debug', action='store_true', dest='debug', default=False,
                            help='enable debug mode')

  # 测试时代码压缩文件的路径
  options_parser.add_option('', '--db-code-dir', action='store', type='string', dest='db_code_dir',
                            help='the directory of miniob\'s code')
  # 测试时代码压缩文件的解压目录
  options_parser.add_option('', '--target-dir', action='store', type='string', dest='target_dir',
                            help='the working directory of miniob database')
  # 解压的目录存在时，是否覆盖
  options_parser.add_option('', '--decompress-overwrite', action='store_true', dest='decompress_overwrite', default=False,
                            help='whether overwrite the decompress target path if exists')
  # 是否需要解压和编译代码
  options_parser.add_option('', '--code-type', action='store', dest='code_type', default='compress',
                            help='compress/git/none. Compress: decompress the code and compile. git: git clone and compile. none: do nothing')
  options_parser.add_option('', '--compile-make-args', action='store', type='string', dest='compile_make_args', default='',
                            help='compile args used by make')
  options_parser.add_option('', '--compile-cmake-args', action='store', type='string', dest='compile_cmake_args', default='',
                            help='compile args used by cmake')
  # 之前已经编译过，是否需要重新编译，还是直接执行make就可以了
  options_parser.add_option('', '--compile-rebuild', action='store_true', default=False, dest='compile_rebuild',
                            help='whether rebuild if build path exists')
  options_parser.add_option('', '--git-repo', action='store', dest='git_repo', 
                            help='the git repo in https')
  options_parser.add_option('', '--git-branch', action='store', dest='git_branch', default='',
                            help='the git repo branch')
  options_parser.add_option('', '--git-repo-prefix', action='store', dest='git_repo_prefix', default='https://github.com',
                            help='the git repo prefix in https')
  options_parser.add_option('', '--git-user', action='store', dest='git_user', default='',
                            help='git user name to download source code')
  options_parser.add_option('', '--git-token', action='store', dest='git_token', default='',
                            help='git token to download source code')

  options, args = options_parser.parse_args(sys.argv[1:])
  return options

def __init_log(options):
  log_level = logging.INFO
  if options.debug:
    log_level = logging.DEBUG
    GlobalConfig.debug = True

  GlobalConfig.debug = True
  log_stream = None
  if 'stdout' == options.log_file:
    log_stream = sys.stdout
  elif 'stderr' == options.log_file:
    log_stream = sys.stderr
  else:
    log_file_dir = os.path.dirname(options.log_file)
    os.makedirs(log_file_dir, exist_ok=True)

  log_format = "%(asctime)s - %(levelname)-5s %(name)s %(lineno)s - %(message)s"
  log_date_format = "%Y-%m-%d %H:%M:%S"

  if log_stream is None:
    logging.basicConfig(level=log_level, filename=options.log_file, format=log_format, datefmt=log_date_format)
  else:
    logging.basicConfig(level=log_level, stream=log_stream, format=log_format, datefmt=log_date_format)

def __init_test_suite(options):
  test_suite = TestSuite()
  test_suite.set_test_case_base_dir(os.path.abspath(options.test_case_base_dir))
  test_suite.set_test_case_scores(os.path.abspath(options.test_case_scores))
  test_suite.set_test_result_base_dir(os.path.abspath(options.test_result_base_dir))
  test_suite.set_test_result_tmp_dir(os.path.abspath(options.test_result_tmp_dir))

  if options.db_base_dir is not None:
    test_suite.set_db_server_base_dir(os.path.abspath(options.db_base_dir))
  if options.db_data_dir is not None:
    test_suite.set_db_data_dir(os.path.abspath(options.db_data_dir))

  test_suite.set_server_port(options.server_port)
  test_suite.set_use_unix_socket(options.use_unix_socket)

  if options.server_started:
    test_suite.donot_need_start_server()

  if options.db_config is not None:
    test_suite.set_db_config(os.path.abspath(options.db_config))

  if options.test_cases is not None:
    test_suite.set_test_names(options.test_cases.split(','))

  if options.report_only:
    test_suite.set_report_only(True)

  return test_suite

def __init_test_suite_with_source_code(options, eval_result):
  os.makedirs(options.target_dir, exist_ok=True)
  target_path = os.path.abspath(options.target_dir)
  proj_path = __get_project_path(target_path)
  build_path = __get_build_path(target_path)

  if options.code_type == 'compress':
    code_path = os.path.abspath(options.db_code_dir)
    if not unzip(code_path, target_path, options.decompress_overwrite):
      message = "decompress the code failed"
      logging.error(message)
      raise Exception(message)
    else:
      logging.info("decompress source code done")
  elif options.code_type == 'git':
    result = git_clone(options.git_repo, options.git_branch, options.git_repo_prefix, 
                        options.git_user, options.git_token, proj_path, 10, eval_result)
    if not result:
      return None

  if not compile(proj_path, build_path, options.compile_cmake_args, options.compile_make_args, options.compile_rebuild, eval_result):
    message = "Failed to compile source code"
    logging.error(message)
    return None

  logging.info("compile source code done")

  # 覆盖一些测试的路径
  logging.info("some config will be override if exists")
  test_suite = __init_test_suite(options)
  test_suite.set_db_data_dir(__get_data_path(target_path))
  test_suite.set_db_server_base_dir(__get_build_path(target_path))
  test_suite.set_db_config(proj_path + '/etc/observer.ini')
  return test_suite

def __run_shell_command(command_args):
  '''
  运行shell命令，返回命令的执行结果码和输出到控制台的信息
  返回的控制台信息是每行一个字符串的字符串列表
  '''

  logging.info("running command: '%s'", ' '.join(command_args))

  outputs = []
  command_process = subprocess.Popen(command_args, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
  while True:
    line = command_process.stderr.readline()
    line_str = line.decode(GlobalConfig.default_encoding)
    if isinstance(line_str, str):
      outputs.append(line_str.strip())
    
    return_code = command_process.poll()
    if return_code is not None:
      return return_code, outputs

def git_pull(to_path: str, timeout:int, eval_result:EvalResult):
  logging.info('running git pull in %s and will wait %d seconds', to_path, timeout)
  command_args = ['git', 'pull']
  process = subprocess.Popen(command_args, cwd=to_path)
  try:
    return_code = process.wait(timeout=timeout)
    if return_code != 0:
      logging.error("Failed to pull source code from repo. return code=%d", return_code)
      return False
    logging.info("pull source code success")
    return True
  except Exception as ex:
    process.kill()
    logging.error("Failed to pull source code from repo. exception=%s", str(ex))
    return False
  return True

def git_clone(repo: str, branch: str, repo_prefix: str, 
              user_name: str, password: str, 
              to_path: str, timeout:int, eval_result: EvalResult):
  '''
  从指定仓库拉取代码。
  to_path： 拉取的代码放的目录。比如 test-tmp/ob_rookie/miniob
  '''
  if os.path.exists(to_path):
    # 目标目录已经存在，可以尝试直接执行git pull
    result = git_pull(to_path, timeout, eval_result)
    if result:  # 如果拉取失败，就尝试重新clone
      return True

    # 清理原有目录，再重新拉取
    logging.info("Failed to pull source code. clean the directory and clone it. path=%s", to_path)
    shutil.rmtree(to_path)

  if not repo.startswith(repo_prefix):
    error = 'git repo must be starts with ' + repo_prefix + ', but got ' + repo
    logging.error(error)
    eval_result.append_message(error)
    return False

  if user_name or password:
    target_repo = repo.replace(repo_prefix, 'https://' + user_name + ':' + password + '@github.com/')
    target_repo_in_log = target_repo.replace(password, '****')
  else:
    target_repo = repo
    target_repo_in_log = target_repo

  logging.info('git clone from %s', target_repo_in_log)
  command_args = ['git', 'clone', target_repo, to_path]
  if len(branch) != 0:
    command_args.append('-b')
    command_args.append(branch)
  process = subprocess.Popen(command_args)
  try:
    return_code = process.wait(timeout=timeout)
    if return_code != 0:
      error = 'Failed to clone repo from ' + target_repo_in_log + ', return code =' + str(return_code)
      logging.error(error)
      eval_result.append_message(error)
      return False
  except Exception as ex:
    process.kill()
    error = 'failed to clone repo from ' + target_repo_in_log + '. exception=' + str(ex)
    logging.error(error)
    eval_result.append_message(error)
    return False
  return True

def unzip(source_dir: str, target_dir: str, overwrite: bool):
  if not os.path.exists(source_dir):
    logging.error('The source_dir %s doesn\'t exist, please provide a vaild source path.', source_dir)
    return False

  if os.path.isdir(target_dir) and len(os.listdir(target_dir)) != 0:
    if overwrite:
      shutil.rmtree(target_dir)
      logging.info("target directory will be cleaned: %s", target_dir)
    else:
      logging.error('target directory is not empty: %s', target_dir)
      return False

  if not os.path.exists(target_dir):
    logging.info("decompress target directory does not exists, try to create it")
    os.makedirs(target_dir)

  ret, outputs = __run_shell_command(["unzip", "-q", "-d", target_dir, source_dir])
  if ret != 0:
    logging.error("Failed to decompress the zip package. source_dir=%s, target_dir=%s",
                  source_dir, target_dir)
    
    for output in outputs:
      logging.error(output)
    return False

  logging.info("decompress the zip package success. source_dir=%s, target_dir=%s",
                source_dir, target_dir)
  return True

def run_cmake(work_dir: str, build_path: str, cmake_args: str):
  cmake_command = ["cmake", "-B", build_path, "--log-level=WARNING"]
  if isinstance(cmake_args, str):
    args = cmake_args.split(';')
    for arg in args:
      arg = arg.strip()
      if len(arg) > 0:
        cmake_command.append(arg)
  cmake_command.append(work_dir)

  ret, outputs = __run_shell_command(cmake_command)
  if ret != 0:
    logging.error("Failed to run cmake command")
    for output in outputs:
      logging.error(output)
    return False, outputs
  return True, []

def compile(work_dir: str, build_dir: str, cmake_args: str, make_args: str, rebuild_all: bool, eval_result: EvalResult):
  '''
  workd_dir是源代码所在目录(miniob目录)
  build_dir 是编译结果的目录
  '''
  if not os.path.exists(work_dir):
    logging.error('The work_dir %s doesn\'t exist, please provide a vaild work path.', work_dir)
    return False

  #now_path = os.getcwd()
  build_path = build_dir
  if os.path.exists(build_path) and rebuild_all:
    logging.info('build directory is not empty but will be cleaned before compile: %s', build_path)
    shutil.rmtree(build_path)

  os.makedirs(build_path, exist_ok=True)
  
  logging.info("start compiling ... build path=%s", build_path)
  ret, outputs = run_cmake(work_dir, build_path, cmake_args)
  if ret == False:
    # cmake 执行失败时，清空整个Build目录，再重新执行一次cmake命令
    shutil.rmtree(build_path)
    os.makedirs(build_path, exist_ok=True)
    ret, outputs = run_cmake(work_dir, build_path, cmake_args)
    if ret == False:
      for output in outputs:
        logging.error(output)
        eval_result.append_message(output)
      return False

  make_command = ["make", "--silent", "-C", build_path]
  if isinstance(make_args, str):
    args = make_args.split(';')
    for arg in args:
      arg = arg.strip()
      if len(arg) > 0:
        make_command.append(arg)

  ret, outputs = __run_shell_command(make_command)
  if ret != 0:
    logging.error("Compile failed")
    for output in outputs:
      logging.error(output.strip())
      eval_result.append_message(output.strip())
    return False

  return True

def run(options):
  '''
  return result, reason
  result: True or False
  
  '''
  __init_log(options)

  logging.info("miniob test starting ...")

  # 由于miniob-test测试程序导致的失败，才认为是失败
  # 比如解压代码失败，git clone超时，目录没有权限等，对miniob-test来说都是成功的
  # git clone由于权限原因失败、编译失败等，对miniob-test来说是成功的
  result = True
  eval_result = EvalResult()

  try:
    test_suite = None
    if options.code_type == 'compress' or options.code_type == 'git':
      test_suite = __init_test_suite_with_source_code(options, eval_result)
    else:
      test_suite = __init_test_suite(options)

    if test_suite != None:
      result = test_suite.run(eval_result)
    # result = True
  except Exception as ex:
    logging.exception(ex)
    result = False
    #eval_result.clear_message()
    eval_result.append_message(str(ex.args))
    eval_result.set_no_cost()
    eval_result.clear_score()

  return result, eval_result.to_json_string()

if __name__ == '__main__':
  os.setpgrp()
  options = __init_options()

  result, evaluation = run(options)

  exit_code = 0
  if result is False:
    exit_code = 1
  else:
    logging.info(evaluation)
  exit(exit_code)

