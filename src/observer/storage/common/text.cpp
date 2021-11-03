//
// Created by 69118 on 2021/11/3.
//

#include "text.h"
#include "common/log/log.h"

RC TextFileHandler::create(const char* file_name) {
  RC rc;
  DiskBufferPool *disk_buffer_pool = theGlobalDiskBufferPool();
  rc = disk_buffer_pool->create_file(file_name);
  if(rc != SUCCESS){
    return rc;
  }
  int file_id;
  rc = disk_buffer_pool->open_file(file_name, &file_id);
  if(rc != RC::SUCCESS){
    LOG_ERROR("Failed to open file. file name=%s, rc=%d:%s", file_name, rc, strrc(rc));
    return rc;
  }
  disk_buffer_pool_ = disk_buffer_pool;
  file_id_ = file_id;
  return rc;
}

RC TextFileHandler::open(const char* file_name) {
  if (disk_buffer_pool_ != nullptr) {
    return RC::RECORD_OPENNED;
  }
  DiskBufferPool *disk_buffer_pool = theGlobalDiskBufferPool();
  int file_id;
  RC rc = disk_buffer_pool->open_file(file_name, &file_id);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  disk_buffer_pool_ = disk_buffer_pool;
  file_id_ = file_id;
  return RC::SUCCESS;
}

RC TextFileHandler::sync() {
  return disk_buffer_pool_->flush_all_pages(file_id_);
}

RC TextFileHandler::close() {
  sync();
  disk_buffer_pool_->close_file(file_id_);
  file_id_ = -1;
  disk_buffer_pool_ = nullptr;
  return RC::SUCCESS;
}

Text::~Text() noexcept {
  close();
}

RC Text::init(const TextFieldMeta &meta) {
  meta_ = meta;
  return RC::SUCCESS;
}

RC Text::create(const char *file_name, const TextFieldMeta &text_field) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  RC rc = init(text_field);
  if (RC::SUCCESS != rc) {
    return rc;
  }
  rc = handler_.create(file_name);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC Text::open(const char *file_name, const TextFieldMeta &text_field) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  RC rc = init(text_field);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = handler_.open(file_name);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC Text::close() {
  if (inited_) {
    handler_.close();
    inited_  = false;
  }
  return RC::SUCCESS;
}

RC Text::sync() {
  return handler_.sync();
}