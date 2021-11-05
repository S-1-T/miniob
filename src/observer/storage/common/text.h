//
// Created by 69118 on 2021/11/3.
//

#ifndef MINIDB_TEXT_H
#define MINIDB_TEXT_H

#include "rc.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/common/field_meta.h"

#define MAX_TEXT_SIZE 4096

class TextFileHandler {
public:
  RC create(const char* file_name);
  RC open(const char* file_name);
  RC close();
  RC sync();

  // 向 TEXT 文件中插入 text 数据，返回页号
  RC insert_content(const char *content, int size, PageNum *page_num);
  // 更新指定 page_num 上的数据。
  RC update_content(const char *content, int size, PageNum page_num);
  // 删除内容
  RC delete_content(PageNum page_num);
  // 获取指定 page_num 上的内容
  RC get_content(char *content, int size, PageNum page_num);
private:
  int file_id_;
  DiskBufferPool *disk_buffer_pool_;
};

class Text {
public:
  Text() = default;
  ~Text() noexcept;

  const TextFieldMeta &meta() const {
    return meta_;
  }

  RC create(const char *file_name, const TextFieldMeta &text_field);
  RC open(const char *file_name, const TextFieldMeta &text_field);
  RC close();
  RC sync();

  RC insert_content(const char *content, int size, PageNum *page_num);
  RC update_content(const char *content, int size, PageNum page_num);
  RC delete_content(PageNum page_num);
  RC get_content(char *content, int size, PageNum page_num);

private:
  bool inited_ = false;
  TextFieldMeta meta_;
  TextFileHandler handler_;

  RC init(const TextFieldMeta &meta);
};


#endif //MINIDB_TEXT_H
