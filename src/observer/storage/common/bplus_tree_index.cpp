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
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/common/bplus_tree_index.h"
#include "common/log/log.h"

BplusTreeIndex::~BplusTreeIndex() noexcept {
  close();
}

RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta, const std::vector<FieldMeta> &fields) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }

  RC rc = Index::init(index_meta, fields);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.create(file_name, fields);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta, const std::vector<FieldMeta> &fields) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  RC rc = Index::init(index_meta, fields_);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.open(file_name);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::close() {
  if (inited_) {
    index_handler_.close();
    inited_ = false;
  }
  return RC::SUCCESS;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid) {
  RC rc = RC::SUCCESS;
  char *pkey = new char[index_handler_.get_total_attr_length()]; 
  int offset = 0; 
  for (size_t i = 0; i < fields_.size(); i++) {
    const FieldMeta &field = fields_[i];
    memcpy(pkey + offset, record + field.offset(), field.len());
    offset += field.len();
  }
  if (index_meta_.is_unique()) {
    RID rid_to_find;
    rc = index_handler_.get_entry(pkey, &rid_to_find);
    if (rc == RC::SUCCESS) {
      LOG_WARN("Index on the key is already exist");
      delete[] pkey;
      return RC::RECORD_DUPLICATE_KEY;
    }
    if (rc != RC::RECORD_INVALID_KEY) {
      LOG_ERROR("Get rid on index failed, rc=%d:%s", rc, strrc(rc));
      delete[] pkey;
      return rc;
    }
  }
  rc = index_handler_.insert_entry(pkey, rid);
  delete[] pkey;
  return rc;
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid) {
  RC rc = RC::SUCCESS;
  char *pkey = new char[index_handler_.get_total_attr_length()]; 
  int offset = 0; 
  for (size_t i = 0; i < fields_.size(); i++) {
    const FieldMeta &field = fields_[i];
    memcpy(pkey + offset, record + field.offset(), field.len());
    offset += field.len();
  }
  rc =  index_handler_.delete_entry(pkey, rid);
  delete[] pkey;
  return rc;
}

IndexScanner *BplusTreeIndex::create_scanner(CompOp comp_op, const char *value) {
  BplusTreeScanner *bplus_tree_scanner = new BplusTreeScanner(index_handler_);
  RC rc = bplus_tree_scanner->open(comp_op, value);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete bplus_tree_scanner;
    return nullptr;
  }

  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(bplus_tree_scanner);
  return index_scanner;
}

RC BplusTreeIndex::sync() {
  return index_handler_.sync();
}

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeScanner *tree_scanner) :
    tree_scanner_(tree_scanner) {
}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept {
  tree_scanner_->close();
  delete tree_scanner_;
}

RC BplusTreeIndexScanner::next_entry(RID *rid) {
  return tree_scanner_->next_entry(rid);
}

RC BplusTreeIndexScanner::destroy() {
  delete this;
  return RC::SUCCESS;
}