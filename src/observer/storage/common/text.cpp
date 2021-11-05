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

RC TextFileHandler::insert_content(const char *content, int size, PageNum *page_num) {
  RC rc = RC::SUCCESS;
  BPPageHandle page_handle;
  rc = disk_buffer_pool_->allocate_page(file_id_, &page_handle);
  if (rc != RC::SUCCESS) {
    LOG_ERROR(
      "Failed to allocate page while inserting text data. file_id: %d, rc:%d:%s",
      file_id_, rc, strrc(rc)
    );
    return rc;
  }
  char *pdata;
  rc = disk_buffer_pool_->get_data(&page_handle, &pdata);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get data. file_id: %d, rc=%d:%s", file_id_, rc, strrc(rc));
    return rc;
  }
  memset(pdata, 0, BP_PAGE_DATA_SIZE);
  if (size > BP_PAGE_DATA_SIZE) {
    size = BP_PAGE_DATA_SIZE;
  }
  memcpy(pdata, content, size);
  rc = disk_buffer_pool_->mark_dirty(&page_handle);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = disk_buffer_pool_->unpin_page(&page_handle);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  *page_num = page_handle.frame->page.page_num;
  return RC::SUCCESS;
}

RC TextFileHandler::update_content(const char *content, int size, PageNum page_num) {
  RC rc = RC::SUCCESS;
  BPPageHandle page_handle;
  rc = disk_buffer_pool_->get_this_page(file_id_, page_num, &page_handle);
  if (rc != RC::SUCCESS) {
    LOG_ERROR(
      "Failed to get text data page. file_id: %d, page_num: %d, rc:%d:%s",
      file_id_, page_num, rc, strrc(rc)
    );
    return rc;
  }
  char *pdata;
  rc = disk_buffer_pool_->get_data(&page_handle, &pdata);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get data. file_id: %d, rc=%d:%s", file_id_, rc, strrc(rc));
    return rc;
  }
  memset(pdata, 0, BP_PAGE_DATA_SIZE);
  if (size > BP_PAGE_DATA_SIZE) {
    size = BP_PAGE_DATA_SIZE;
  }
  memcpy(pdata, content, size);
  rc = disk_buffer_pool_->mark_dirty(&page_handle);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return disk_buffer_pool_->unpin_page(&page_handle);
}

RC TextFileHandler::delete_content(PageNum page_num) {
  return disk_buffer_pool_->dispose_page(file_id_, page_num); 
}

RC TextFileHandler::get_content(char *content, int size, PageNum page_num) {
  RC rc = RC::SUCCESS;
  BPPageHandle page_handle;
  rc = disk_buffer_pool_->get_this_page(file_id_, page_num, &page_handle);
  if (rc != RC::SUCCESS) {
    LOG_ERROR(
      "Failed to get text data page. file_id: %d, page_num: %d, rc:%d:%s",
      file_id_, page_num, rc, strrc(rc)
    );
    return rc;
  }
  char *pdata;
  rc = disk_buffer_pool_->get_data(&page_handle, &pdata);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get data. file_id: %d, rc=%d:%s", file_id_, rc, strrc(rc));
    return rc;
  }
  // 需要保证 content 已分配内存
  memcpy(content, pdata, size);
  return disk_buffer_pool_->unpin_page(&page_handle); 
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

RC Text::insert_content(const char *content, int size, PageNum *page_num) {
  return handler_.insert_content(content, size, page_num);
}

RC Text::update_content(const char *content, int size, PageNum page_num) {
  return handler_.update_content(content, size, page_num);
}

RC Text::delete_content(PageNum page_num) {
  return handler_.delete_content(page_num);
}

RC Text::get_content(char *content, int size, PageNum page_num) {
  return handler_.get_content(content, size, page_num);
}