/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <string>
#include <sstream>
#include <vector>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "storage/common/type/convert.h"

using namespace common;

RC create_selection_executor(Trx *trx, const Selects &selects, Table *table, SelectExeNode &select_node);

RC do_cartesian(std::vector<TupleSet> &tuple_sets, const int condition_num, Condition *conditions, TupleSet &output);

RC cartesian(std::vector<TupleSet> &tuple_sets, int condition_num, Condition *conditions, std::shared_ptr<TupleValue> *values, int value_num, TupleSet &output, int index);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new(std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new(std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  char response[256] = "";
  switch (sql->flag) {
    case SCF_SELECT: {  // select
      RC rc =
          do_select(current_db, sql, exe_event->sql_event()->session_event());
      // 出错时返回 FAILURE
      if (rc != RC::SUCCESS) snprintf(response, sizeof(response), "FAILURE\n");
    }
      break;

    case SCF_INSERT:
    case SCF_UPDATE:
    case SCF_DELETE:
    case SCF_CREATE_TABLE:
    case SCF_SHOW_TABLES:
    case SCF_DESC_TABLE:
    case SCF_DROP_TABLE:
    case SCF_CREATE_INDEX:
    case SCF_DROP_INDEX:
    case SCF_LOAD_DATA: {
      StorageEvent *storage_event = new(std::nothrow) StorageEvent(exe_event);
      if (storage_event == nullptr) {
        LOG_ERROR("Failed to new StorageEvent");
        event->done_immediate();
        return;
      }

      default_storage_stage_->handle_event(storage_event);
    }
      break;
    case SCF_SYNC: {
      RC rc = DefaultHandler::get_default().sync();
      snprintf(response, sizeof(response), "%s\n", strrc(rc));
    }
      break;
    case SCF_BEGIN: {
      session_event->get_client()->session->set_trx_multi_operation_mode(true);
      snprintf(response, sizeof(response), "%s\n", strrc(RC::SUCCESS));
    }
      break;
    case SCF_COMMIT: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->commit();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      snprintf(response, sizeof(response), "%s\n", strrc(rc));
    }
      break;
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      snprintf(response, sizeof(response), "%s\n", strrc(rc));
    }
      break;
    case SCF_HELP: {
      snprintf(response, sizeof(response),
               "show tables;\n"
               "desc `table name`;\n"
               "create table `table name` (`column name` `column type`, ...);\n"
               "drop table `table name`;\n"
               "create index `index name` on `table` (`column`);\n"
               "drop index `index name` on 'table';\n"
               "insert into `table` values(`value1`,`value2`);\n"
               "update `table` set column=value [where `column`=`value`];\n"
               "delete from `table` [where `column`=`value`];\n"
               "select [ * | `columns` ] from `table`;\n");
    }
      break;
    case SCF_EXIT: {
      // do nothing
      snprintf(response, sizeof(response), "Unsupported\n");
    }
      break;
    default: {
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
  }
  if (strlen(response) > 0) session_event->set_response(response);
  exe_event->done_immediate();
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
  return RC::SUCCESS;
}

// 检查二义性，并得到正确时的表 index
RC check_ambiguous(size_t relation_num, Table **tables, const char *attribute_name, size_t &idx) {
  bool find = false;
  for (size_t j = 0; j < relation_num; j++) {
    auto f = tables[j]->table_meta().field(attribute_name);
    if (f != nullptr) {
      if (!find) {
        find = true;
        idx = j;
      } else {
        LOG_WARN("Column [%s] in field list is ambiguous", attribute_name);
        return RC::SCHEMA_FIELD_EXIST;
      }
    }
  }
  // 没有表有此字段
  if (!find) {
    LOG_WARN("No table has field [%s]", attribute_name);
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }
  return RC::SUCCESS;
}

// 统一进行 meta 检测, 返回找到的 tables
// 并为多表构造输出的 schema
RC ExecuteStage::selects_meta_check(const char *db, const Selects &selects, Table **tables, TupleSchema &output_schema) {
  // 首先检测 table
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    Table * table = DefaultHandler::get_default().find_table(db, table_name);
    if (nullptr == table) {
      LOG_WARN("No such table [%s] in db [%s]", table_name, db);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    tables[i] = table;
  }
  // 检测 attr 中的 table 是否存在于要查找的 tables 中
  // 以及 attr 是否存在于此 table 的 fields 中
  // 并为多表查询构造 output_schema
  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    if (attr.relation_name != nullptr) {
      Table *t = nullptr;
      for (size_t j = 0; j < selects.relation_num; j++) {
        if (0 == strcmp(attr.relation_name, selects.relations[j])) {
          t = tables[j];
          break;
        }
      }
      if (t == nullptr) {
        LOG_WARN("Table [%s] is not in selection's relations", attr.relation_name);
        return RC::MISMATCH;
      }
      if (0 == strcmp("*", attr.attribute_name)) {
        TupleSchema temp;
        TupleSchema::from_table(t, temp);
        output_schema.append(temp);
      } else if (nullptr == t->table_meta().field(attr.attribute_name)) {
        LOG_WARN("No such field [%s] in table [%s]", attr.attribute_name, attr.relation_name);
        return RC::SCHEMA_FIELD_NOT_EXIST;
      } else {
        schema_add_field(t, attr.attribute_name, output_schema);
      }
    } else if (0 == strcmp("*", attr.attribute_name)) {
      for (int j = selects.relation_num - 1; j >= 0; j--) {
        TupleSchema temp;
        TupleSchema::from_table(tables[j], temp);
        output_schema.append(temp);
      }
    } else {
      // 检测二义性
      size_t idx = 0;
      RC rc = check_ambiguous(selects.relation_num, tables, attr.attribute_name, idx);
      if (RC::SUCCESS != rc) {
        return rc;
      }
      schema_add_field(tables[idx], attr.attribute_name, output_schema);
    }
  }
  // 检测 condition 中的 attr 是否存在于要查找的 tables 中
  // 以及此 attr 是否存在于此 table 的 fields 中
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    const char *left_table_name = condition.left_attr.relation_name;
    const char *right_table_name = condition.right_attr.relation_name;
    const char *left_attr_name = condition.left_attr.attribute_name;
    const char *right_attr_name = condition.right_attr.attribute_name;
    bool left_is_attr = condition.left_is_attr;
    bool right_is_attr = condition.right_is_attr;
    bool left_find = false;
    bool right_find = false;
    size_t left_table_idx = 0;
    size_t right_table_idx = 0;
    for (size_t j = 0; j < selects.relation_num; j++) {
      if (left_is_attr) {
        if (left_table_name != nullptr && 0 == strcmp(left_table_name, selects.relations[j])) {
          left_find = true;
          left_table_idx = j;
        } else if (left_table_name == nullptr) {
          size_t idx = 0;
          RC rc = check_ambiguous(selects.relation_num, tables, left_attr_name, idx);
          if (RC::SUCCESS != rc) {
            return rc;
          }
        }
      }
      if (right_is_attr) {
        if (right_table_name != nullptr && 0 == strcmp(right_table_name, selects.relations[j])) {
          right_find = true;
          right_table_idx = j;
        } else if (right_table_name == nullptr) {
          size_t idx = 0;
          RC rc = check_ambiguous(selects.relation_num, tables, right_attr_name, idx);
          if (RC::SUCCESS != rc) {
            return rc;
          }
        }
      }
    }
    if (left_is_attr && left_table_name != nullptr && !left_find) {
      LOG_WARN("left attr's relation [%s] will not be scanned", left_table_name);
      return RC::MISMATCH;
    }
    if (right_is_attr && right_table_name != nullptr && !right_find) {
      LOG_WARN("right attr's relation [%s] will not be scanned", right_table_name);
      return RC::MISMATCH;
    }
    if (left_is_attr && left_table_name != nullptr &&
      nullptr == tables[left_table_idx]->table_meta().field(left_attr_name)) {
      LOG_WARN("left attr [%s] is not exist in [%s]", left_attr_name, left_table_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    if (right_is_attr && right_table_name != nullptr &&
        nullptr == tables[right_table_idx]->table_meta().field(right_attr_name)) {
      LOG_WARN("right attr [%s] is not exist in [%s]", right_attr_name, right_table_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }
  return RC::SUCCESS;
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  Table *tables[selects.relation_num];
  TupleSchema output_schema; // 用于输出展示的 schema, 只用于多表查询
  rc = selects_meta_check(db, selects, tables, output_schema);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Selection meta test failed");
    return rc;
  }

  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, tables[i], *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *&tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    }
    select_nodes.push_back(select_node);
  }
  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node: select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *&tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  if (tuple_sets.size() > 1) {
    // 本次查询了多张表，需要做join操作
    // 提取两边都是 attr 且表不一样的 condition
    int remain_condition_num = 0;
    Condition remain_conditions[MAX_NUM];
    for (int i = 0; i < selects.condition_num; i++) {
      const Condition &condition = selects.conditions[i];
      if (condition.left_is_attr && condition.right_is_attr &&
          condition.left_attr.relation_name != condition.right_attr.relation_name) {
        remain_conditions[remain_condition_num++] = condition;
      }
    }
    // 将笛卡尔积整合到一个 tuple set 中打印输出。
    TupleSet output(output_schema);
    auto rc = do_cartesian(tuple_sets, remain_condition_num, remain_conditions, output);
    if (rc != RC::SUCCESS && rc != RC::MISMATCH) {
      return rc;
    }
    output.set_schema(output_schema);
    output.print(ss, true);
  } else {
    // 当前只查询一张表，直接返回结果即可
    tuple_sets.front().print(ss, false);
  }

  for (SelectExeNode *&tmp_node: select_nodes) {
    delete tmp_node;
  }
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}

// do_cartesian 将多表做笛卡尔积，返回一个 TupleSet，
// 其中会用 selects 中的涉及两个表的 condition 进行过滤，
// 不用考虑其他单表 condition，因为已经在 scan 阶段过滤。
RC do_cartesian(std::vector<TupleSet> &tuple_sets, const int condition_num, Condition *conditions, TupleSet &output) {
  RC rc = RC::SUCCESS;
  TupleSchema new_schema;
  TupleSchema output_schema = output.schema();
  // 先添加的 tuple set 放前面
  int table_num = tuple_sets.size();
  for (int i = table_num - 1; i >= 0; i--) {
    TupleSet &tuple_set = tuple_sets[i];
    new_schema.append(tuple_set.get_schema());
  }
  // 冗余处理
  new_schema.append(output_schema);
  output = TupleSet(new_schema);
  auto *values = new std::shared_ptr<TupleValue>[new_schema.fields().size()];
  rc = cartesian(tuple_sets, condition_num, conditions, values, 0, output, table_num - 1);
  delete[] values;
  return rc;
}

// 超出 6 个参数，
// 直接通过参数存取 value_num 的性能与每次计算 value_num 的性能谁更高未知
RC cartesian(std::vector<TupleSet> &tuple_sets, int condition_num, Condition *conditions, std::shared_ptr<TupleValue> *values, int value_num, TupleSet &output, int index) {

  /*
   * schema 的结构为： tuple_sets 中 schema 的倒续连接 + 直接要输出的 schema
   * 例如：
   * 如果 tuple_sets 的 schema 为 [[t1.a, t1.b], [t2.a, t2.b]]，
   * output_schema 为 [t2.b, t1.a]，
   * 则下方 schema 的结构为 [t2.a, t2.b, t1.a, t1.b, t2.b, t1.a]。
   * 由于 values 的顺序和前半部分 （[t2.a, t2.b, t1.a, t1.b]） 相同，
   * 所以在组成 tuple 时直接用后半部分的 （[t2.b, t1.a]）去前半部分（[t2.a, t2.b, t1.a, t1.b]）找对应 value。
   * 再由一个临时数组存储要生成一整个 tuple 的 values，由它生成 tuple 放入 TupleSet output 中。
   * 在 TupleSet 收集完成后再将其 schema 替换为后半部分。
   * 由此完成 Projection 操作。
   */
  auto &schema = output.schema();
  auto &current_set = tuple_sets[index];
  if (value_num > 0) {
    // 对笛卡尔积生成的结果做条件过滤, 判断 condition，便于提前剪枝
    for (int i = 0; i < condition_num; i++) {
      Condition &condition = conditions[i];
      int left_idx = schema.index_of_field(condition.left_attr.relation_name, condition.left_attr.attribute_name);
      int right_idx = schema.index_of_field(condition.right_attr.relation_name, condition.right_attr.attribute_name);
      if (left_idx >= value_num || right_idx >= value_num) {
        continue;
      }
      const TupleValue *left = values[left_idx].get();
      const TupleValue *right = values[right_idx].get();
      if (!is_type_convertable(left->type(), right->type())) {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      if (!left->compare_with_op(*right, condition.comp)) {
        return RC::MISMATCH;
      }
    }
  }
  if (index == -1) {
    Tuple output_tuple;
    // 进行投影，按照 output 的 schema 重组字段，原理见上面的注释。
    int output_num = schema.fields().size() - value_num;
    std::shared_ptr<TupleValue> output_value[output_num];
    for (int i = 0; i < output_num; i++) {
      auto field = schema.field(value_num + i);
      int val_idx = schema.index_of_field(field.table_name(), field.field_name());
      output_value[i] = values[val_idx];
    }
    for (int i = 0; i < output_num; i++) {
      // 只加入要 select 的字段
      output_tuple.add(output_value[i]);
    }
    output.add(std::move(output_tuple));
    return RC::SUCCESS;
  }
  for (int i = 0; i < current_set.size(); i++) {
    auto & current_tuple = current_set.get(i);
    int current_tuple_size = current_tuple.size();
    for (int j = 0; j < current_tuple_size; j++) {
      values[value_num + j] = current_tuple.get_pointer(j);
    }
    value_num += current_tuple_size;
    auto rc = cartesian(tuple_sets, condition_num, conditions, values, value_num, output, index - 1);
    if (rc != RC::SUCCESS && rc != RC::MISMATCH) {
      return rc;
    }
    value_num -= current_tuple_size;
  }
  return RC::SUCCESS;
}

bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, Table *table, SelectExeNode &select_node) {
  // 列出跟这张表关联的Attr
  TupleSchema schema;
  const char *table_name = table->name();
  select_node.set_aggregation(selects.aggregation_num == 0);

  std::unordered_map<const AggregationType*, AggregationInfo> aggregationInfos;
  for (int i = 0; i < selects.aggregation_num; i++) {
    aggregationInfos.insert(std::make_pair(&selects.aggregationType[i], AggregationInfo(selects.aggregationType[i])));
  }

  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
      if (0 == strcmp("*", attr.attribute_name)) {
        // 列出这张表所有字段
        TupleSchema::from_table(table, schema);
        break; // 没有校验，给出* 之后，再写字段的错误
      } else {
        // 列出这张表相关字段
        RC rc = schema_add_field(table, attr.attribute_name, schema);
        if (match_table(selects, attr.relation_name, table_name) && rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    } else if (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
      condition.left_attr.relation_name != nullptr && condition.left_attr.relation_name != condition.right_attr.relation_name) {
      schema_add_field(table, condition.left_attr.attribute_name, schema);
      schema_add_field(table, condition.right_attr.attribute_name, schema);
    }
  }

  return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
}
