//
// Created by 69118 on 2021/11/3.
//

#ifndef MINIDB_TEXT_H
#define MINIDB_TEXT_H

#include "rc.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/common/field_meta.h"

class TextFileHandler {
public:
  RC create(const char* file_name);
  RC open(const char* file_name);
  RC close();
  RC sync();
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

  RC get_content(int page_num, char * content);
  RC update_content(int page_num, const char* content);

private:
  bool inited_ = false;
  TextFieldMeta meta_;
  TextFileHandler handler_;

  RC init(const TextFieldMeta &meta);
};


#endif //MINIDB_TEXT_H
