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
// Created by Wangyunlai on 2021/5/13.
//

#include "storage/common/table.h"

#include <limits.h>
#include <string.h>

#include <algorithm>
#include <ctime>

#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/common/bplus_tree_index.h"
#include "storage/common/condition_filter.h"
#include "storage/common/text.h"
#include "storage/common/meta_util.h"
#include "storage/trx/trx.h"
#include "storage/common/type/convert.h"
#include "storage/common/text.h"
#include "storage/common/type/convert.h"
#include "storage/common/type/date.h"

Table::Table()
  : data_buffer_pool_(nullptr), file_id_(-1), record_handler_(nullptr) {}

Table::~Table() {
  delete record_handler_;
  record_handler_ = nullptr;

  if (data_buffer_pool_ != nullptr && file_id_ >= 0) {
    data_buffer_pool_->close_file(file_id_);
    data_buffer_pool_ = nullptr;
  }

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(const char *path, const char *name, const char *base_dir,
         int attribute_count, const AttrInfo attributes[]) {
  if (nullptr == name || common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN(
      "Invalid arguments. table_name=%s, attribute_count=%d, "
      "attributes=%p",
      name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // ?????? table_name.table???????????????????????????
  // ?????????????????????????????????

  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (-1 == fd) {
    if (EEXIST == errno) {
      LOG_ERROR(
        "Failed to create table file, it has been created. %s, EEXIST, "
        "%s",
        path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path,
          errno, strerror(errno));
    return RC::IOERR;
  }

  ::close(fd);

  // ????????????
  if ((rc = table_meta_.init(name, attribute_count, attributes)) !=
    RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  // ?????? text ??????
  int field_num = table_meta_.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field = table_meta_.field(i);
    if (field->type() == TEXTS) {
      rc = create_text_field(base_dir, field->name());
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create text field %s file for table %s",
                  field->name(), name);
        return rc;
      }
    }
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s",
          path, strerror(errno));
    return RC::IOERR;
  }

  // ???????????????????????????
  table_meta_.serialize(fs);
  fs.close();

  std::string data_file =
    std::string(base_dir) + "/" + name + TABLE_DATA_SUFFIX;
  data_buffer_pool_ = theGlobalDiskBufferPool();
  rc = data_buffer_pool_->create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR(
      "Failed to create disk buffer pool of data file. file name=%s",
      data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);

  base_dir_ = base_dir;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::open(const char *meta_file, const char *base_dir) {
  // ?????????????????????
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + "/" + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s",
          meta_file, strerror(errno));
    return RC::IOERR;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file);
    return RC::GENERIC_ERROR;
  }
  fs.close();

  // ??????????????????
  RC rc = init_record_handler(base_dir);

  base_dir_ = base_dir;

  const int text_field_num = table_meta_.text_field_num();
  for (int i = 0; i < text_field_num; i++) {
    const TextFieldMeta *text_field_meta = table_meta_.text_field(i);
    if (text_field_meta == nullptr) {
      LOG_PANIC(
        "Found invalid text field meta info which has a non-exists field. "
        "table=%s, field=%s",
        name(), text_field_meta->name());
      return RC::GENERIC_ERROR;
    }
    Text *text = new Text;
    std::string text_file = text_data_file(base_dir_.c_str(), name(), text_field_meta->name());
    rc = text->open(text_file.c_str(), *text_field_meta);
    if (rc != RC::SUCCESS) {
      delete text;
      LOG_ERROR(
        "Failed to open text file. table=%s,  file=%s, rc=%d:%s",
        name(), text_file.c_str(), rc, strrc(rc));
      return rc;
    }
    texts_.push_back(text);
  }

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    const std::vector<std::string> &index_fields = index_meta->fields();
    std::vector<FieldMeta> fields(index_fields.size());
    for (size_t j = 0; j < index_fields.size(); j++) {
      const FieldMeta *field_meta = table_meta_.field(index_fields[j].c_str());
      if (field_meta == nullptr) {
        LOG_PANIC(
          "Found invalid index meta info which has a non-exists field. "
          "table=%s, index=%s, field=%s",
          name(), index_meta->name(), index_fields[j].c_str());
        return RC::GENERIC_ERROR;
      }
      fields[i] = *field_meta;
    }
    
    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file =
      index_data_file(base_dir, name(), index_meta->name());
    rc = index->open(index_file.c_str(), *index_meta, fields);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR(
        "Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
        name(), index_meta->name(), index_file.c_str(), rc, strrc(rc));
      return rc;
    }
    indexes_.push_back(index);
  }
  return rc;
}

RC Table::close() {
  sync();
  data_buffer_pool_->close_file(file_id_);

  file_id_ = -1;
  data_buffer_pool_ = nullptr;
  record_handler_ = nullptr;

  return RC::SUCCESS;
}

RC Table::commit_insert(Trx *trx, const RID &rid) {
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->commit_insert(this, record);
}

RC Table::rollback_insert(Trx *trx, const RID &rid) {
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // remove all indexes
  rc = delete_entry_of_indexes(record.data, rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR(
      "Failed to delete indexes of record(rid=%d.%d) while rollback "
      "insert, rc=%d:%s",
      rid.page_num, rid.slot_num, rc, strrc(rc));
  } else {
    rc = record_handler_->delete_record(&rid);
  }
  return rc;
}

RC Table::insert_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;

  if (trx != nullptr) {
    trx->init_trx_info(this, *record);
  }
  rc = record_handler_->insert_record(record->data, table_meta_.record_size(),
                    &record->rid);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s",
          table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->insert_record(this, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to log operation(insertion) to trx");

      RC rc2 = record_handler_->delete_record(&record->rid);
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC(
          "Failed to rollback record data when insert index entries "
          "failed. table name=%s, rc=%d:%s",
          name(), rc2, strrc(rc2));
      }
      return rc;
    }
  }

  for (int i = 0; i < indexes_.size(); i++) {
    rc = indexes_[i]->insert_entry(record->data, &record->rid);
    if (rc != RC::SUCCESS) {
      // rollback
      RC rc2;
      for (int j = 0; j < i; j++) {
        rc2 = indexes_[j]->delete_entry(record->data, &record->rid);
        if (rc2 != RC::SUCCESS && rc2 != RC::RECORD_INVALID_KEY) {
          LOG_PANIC(
              "Failed to rollback index data when insert index entries "
              "failed. table name=%s, rc=%d:%s",
              name(), rc2, strrc(rc2));
        }
      }
      if (rc != RC::RECORD_DUPLICATE_KEY) {
        rc2 = indexes_[i]->delete_entry(record->data, &record->rid);
        if (rc2 != RC::SUCCESS && rc2 != RC::RECORD_INVALID_KEY) {
          LOG_PANIC(
              "Failed to rollback index data when insert index entries "
              "failed. table name=%s, rc=%d:%s",
              name(), rc2, strrc(rc2));
        }
      }
      rc2 = trx->delete_record(this, record);
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC(
            "Failed to rollback record data when insert index entries "
            "failed. table name=%s, rc=%d:%s",
            name(), rc2, strrc(rc2));
      }
      rc2 = record_handler_->delete_record(&record->rid);
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC(
            "Failed to rollback record data when insert index entries "
            "failed. table name=%s, rc=%d:%s",
            name(), rc2, strrc(rc2));
      }
      return rc;
    }
  }
  return rc;
}

RC Table::insert_record(Trx *trx, int value_num, const Value *values) {
  if (value_num <= 0 || nullptr == values) {
    LOG_ERROR("Invalid argument. value num=%d, values=%p", value_num,
          values);
    return RC::INVALID_ARGUMENT;
  }

  char *record_data = nullptr;
  RC rc = make_record(value_num, values, record_data);
  if (rc != RC::SUCCESS) {
    if (record_data != nullptr) {
      delete[] record_data;
    }
    LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  Record record;
  record.data = record_data;
  // record.valid = true;
  rc = insert_record(trx, &record);
  delete[] record_data;
  return rc;
}

RC Table::insert_records(Trx *trx, int tuple_num, const InsertTuple *tuples) {
  // ???????????? tuple ??? meta ??????
  RC rc = RC::SUCCESS;
  char* records[tuple_num];
  for (int i = 0; i < tuple_num; i++) {
    const InsertTuple &tuple = tuples[i];
    char *record_data = nullptr;
    rc = make_record(tuple.value_num, tuple.values, record_data);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
      for (int j = 0; j < i; j++) {
        delete[] records[j];
      }
      return rc;
    }
    records[i] = record_data;
  }

  Record temp[tuple_num];
  for (int i = 0; i < tuple_num; i++) {
    Record record;
    record.data = records[i];
    rc = insert_record(trx, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to insert a record, rc=%d:%s", rc, strrc(rc));
      RC rc2;
      // rollback
      // ?????????????????????????????????????????????????????????????????????????????????????????????
      for (int j = 0; j < i; j++) {
        rc2 = delete_record(nullptr, &temp[j]);
        if (rc2 != RC::SUCCESS) {
          LOG_PANIC("Rollback inserts failed, rc=%d:%s", rc2, strrc(rc2));
        }
      }
      break;
    }
    temp[i] = record;
  }

  for (int i = 0; i < tuple_num; i++) {
    delete[] records[i];
  }
  return rc;
}

const char *Table::name() const { return table_meta_.name(); }

const TableMeta &Table::table_meta() const { return table_meta_; }

RC Table::make_record(int value_num, const Value *values, char *&record_out) {
  // ??????????????????????????????
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    return RC::SCHEMA_FIELD_MISSING;
  }
  // ??????????????????????????????
  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field =
      table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];
    // ??????????????????????????? NULL
    if (!field->nullable() && value.is_null) {
      LOG_ERROR("Field %s is not nullable, but value is null", field->name());
      return RC::CONSTRAINT_NOTNULL;
    }
    // ?????? Meta ???????????????????????????
    if (!is_type_convertable(field->type(), value.type)) {
      LOG_ERROR(
        "Invalid value type. field name=%s, type=%d, but "
        "given=%d",
        field->name(), field->type(), value.type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }
  // ????????????????????????
  int record_size = table_meta_.record_size();
  char *record = new char[record_size];
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field =
      table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];
    if (convert_type(field->name(), value.type, value.data, field->type(),
                     record + field->offset(), field->len(), value.is_null) != RC::SUCCESS) {
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }
  record_out = record;
  return RC::SUCCESS;
}

Text* Table::text(int index) {
  if (index < 0 || index >= texts_.size()) {
    return nullptr;
  }
  return texts_[index];
}

RC Table::convert_type(const char *field_name, AttrType src_type, void *src_data, AttrType dest_type, void *dest_data, int len, bool is_null) {
  // ????????????????????? len - 1
  // ?????? 1 ????????????????????? NULL
  // ????????? NULL ??????????????????????????????????????????
  len = len - 1;
  if (is_null) {
    memset(dest_data, 0, len);
    *((char *)dest_data + len) = (char)true;
    return RC::SUCCESS;
  }
  if (!is_type_convertable(src_type, dest_type)) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  switch (dest_type) {
    // INTS FLOATS ??????????????????
    case INTS: {
      if (src_type == FLOATS) {
        float origin = *(float *) src_data;
        int convert = (int) origin;
        memcpy(dest_data, &convert, len);
      } else {
        memcpy(dest_data, src_data, len);
      }
      break;
    }
    case FLOATS: {
      if (src_type == INTS) {
        int origin = *(int *) src_data;
        float convert = (float) origin;
        memcpy(dest_data, &convert, len);
      } else {
        memcpy(dest_data, src_data, len);
      }
      break;
    }
    case CHARS: {
      memcpy(dest_data, src_data, std::min(len, (int)strlen(static_cast<char *>(src_data)) + 1));
      break;
    }
    case DATES: {
      try {
        Date date = Date(static_cast<char *>(src_data));
        time_t date_time_t = date.get_inner_date_time_t();
        memcpy(dest_data, &date_time_t, len);
      } catch (const char *e) {
        LOG_ERROR("Invalid value data to create a Date type. e=%s",
                  e);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      break;
    }
    case TEXTS: {
      TextHeader text_header;
      text_header.remain_content_page_num = BP_INVALID_PAGE_NUM;
      const char *text_data = (char *)src_data;
      int text_len = strlen(text_data);
      if (text_len > MAX_TEXT_SIZE) {
        text_len = MAX_TEXT_SIZE;
      }
      text_header.length = text_len;
      if (text_len <= TEXT_PREVIOUS_DATA_SIZE) {
        memcpy(text_header.previous_content, text_data, text_len);
      } else {
        memcpy(text_header.previous_content, text_data, TEXT_PREVIOUS_DATA_SIZE);
        int text_field_num = table_meta_.text_field_num();
        int i = 0;
        for (i = 0; i < text_field_num; i++) {
          const TextFieldMeta *text_field_meta = table_meta_.text_field(i);
          if (text_field_meta == nullptr) {
            return RC::SCHEMA_FIELD_MISSING;
          }
          if (0 == strcmp(text_field_meta->name(), field_name)) {
            break;
          }
        }
        if (i == text_field_num) {
          return RC::SCHEMA_FIELD_MISSING;
        }
        Text *text = texts_[i];
        int page_num = 0;
        RC rc = text->insert_content(text_data + TEXT_PREVIOUS_DATA_SIZE, text_len - TEXT_PREVIOUS_DATA_SIZE, &page_num);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Failed to insert text content. rc=%d:%s", rc, strrc(rc));
          return rc;
        }
        text_header.remain_content_page_num = page_num;
      }
      memcpy(dest_data, &text_header, len);
      break;
    }
    default:
      memcpy(dest_data, src_data, len);
  }
  // ????????????????????????????????? null
  *((char *)dest_data + len) = (char)false;
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir) {
  std::string data_file =
    std::string(base_dir) + "/" + table_meta_.name() + TABLE_DATA_SUFFIX;
  if (nullptr == data_buffer_pool_) {
    data_buffer_pool_ = theGlobalDiskBufferPool();
  }

  int data_buffer_pool_file_id;
  RC rc = data_buffer_pool_->open_file(data_file.c_str(),
                     &data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s",
          data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc = record_handler_->init(*data_buffer_pool_, data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  file_id_ = data_buffer_pool_file_id;
  return rc;
}

/**
 * ????????????Record???????????????????????????
 */
class RecordReaderScanAdapter {
   public:
  explicit RecordReaderScanAdapter(void (*record_reader)(const char *data,
                               void *context),
                   void *context)
    : record_reader_(record_reader), context_(context) {}

  void consume(const Record *record) {
    record_reader_(record->data, context_);
  }

   private:
  void (*record_reader_)(const char *, void *);

  void *context_;
};

static RC scan_record_reader_adapter(Record *record, void *context) {
  RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *)context;
  adapter.consume(record);
  return RC::SUCCESS;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit,
            void *context,
            void (*record_reader)(const char *data, void *context)) {
  RecordReaderScanAdapter adapter(record_reader, context);
  return scan_record(trx, filter, limit, (void *)&adapter,
             scan_record_reader_adapter);
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit,
            void *context,
            RC (*record_reader)(Record *record, void *context)) {
  if (nullptr == record_reader) {
    return RC::INVALID_ARGUMENT;
  }

  if (0 == limit) {
    return RC::SUCCESS;
  }

  if (limit < 0) {
    limit = INT_MAX;
  }

  IndexScanner *index_scanner = find_index_for_scan(filter);
  if (index_scanner != nullptr) {
    return scan_record_by_index(trx, index_scanner, filter, limit, context,
                  record_reader);
  }

  RC rc = RC::SUCCESS;
  RecordFileScanner scanner;
  rc = scanner.open_scan(*data_buffer_pool_, file_id_, filter);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. file id=%d. rc=%d:%s", file_id_, rc,
          strrc(rc));
    return rc;
  }

  int record_count = 0;
  Record record;
  rc = scanner.get_first_record(&record);
  for (; RC::SUCCESS == rc && record_count < limit;
     rc = scanner.get_next_record(&record)) {
    if (trx == nullptr || trx->is_visible(this, &record)) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        break;
      }
      record_count++;
    }
  }

  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_ERROR("failed to scan record. file id=%d, rc=%d:%s", file_id_, rc,
          strrc(rc));
  }
  scanner.close_scan();
  return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner,
                 ConditionFilter *filter, int limit,
                 void *context,
                 RC (*record_reader)(Record *, void *)) {
  RC rc = RC::SUCCESS;
  RID rid;
  Record record;
  int record_count = 0;
  while (record_count < limit) {
    rc = scanner->next_entry(&rid);

    if (rc == RC::RECORD_NO_MORE_IDX_IN_MEM) {
      continue;
    }

    if (rc != RC::SUCCESS) {
      if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
        break;
      }
      LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
      break;
    }

    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s",
            rid.page_num, rid.slot_num, rc, strrc(rc));
      break;
    }

    if ((trx == nullptr || trx->is_visible(this, &record)) &&
      (filter == nullptr || filter->filter(record))) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        LOG_TRACE("Record reader break the table scanning. rc=%d:%s",
              rc, strrc(rc));
        break;
      }
    }

    record_count++;
  }

  scanner->destroy();
  return rc;
}

class IndexInserter {
   public:
  explicit IndexInserter(Index *index) : index_(index) {}

  RC insert_index(const Record *record) {
    return index_->insert_entry(record->data, &record->rid);
  }

   private:
  Index *index_;
};

static RC insert_index_record_reader_adapter(Record *record, void *context) {
  IndexInserter &inserter = *(IndexInserter *)context;
  return inserter.insert_index(record);
}

RC Table::create_index(Trx *trx, const char *index_name,
             const char *attribute_names[], size_t attr_num, bool is_unique) {
  if (index_name == nullptr || common::is_blank(index_name) ||
    attribute_names == nullptr || attr_num == 0) {
    return RC::INVALID_ARGUMENT;
  }
  std::vector<std::string> index_field_names(attr_num);
  std::vector<FieldMeta> fields;
  for (int i = attr_num - 1; i >= 0; i--) {
    index_field_names[i] = attribute_names[i];
    const FieldMeta *field_meta = table_meta_.field(attribute_names[i]);
    if (!field_meta) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.emplace_back(*field_meta);
  }

  if (table_meta_.index(index_name) != nullptr ||
    table_meta_.find_index_by_fields(index_field_names)) {
    return RC::SCHEMA_INDEX_EXIST;
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, fields, is_unique);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // ????????????????????????
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file =
    index_data_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, fields);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s",
          index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // ????????????????????????????????????????????????
  IndexInserter index_inserter(index);
  rc = scan_record(trx, nullptr, -1, &index_inserter,
           insert_index_record_reader_adapter);
  if (rc != RC::SUCCESS) {
    // rollback
    RC close_rc = index->close();
    if (close_rc != RC::SUCCESS) {
      LOG_PANIC("Failed to close index file (%s) on table (%s). error=%d:%s",
                index_file.c_str(), name(), close_rc, strrc(close_rc));
    }
    remove(index_file.c_str());
    delete index;
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s",
          name(), rc, strrc(rc));
    return rc;
  }
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s",
          index_name, name(), rc, strrc(rc));
    return rc;
  }
  // ???????????????????????????
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file,
      std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s",
          tmp_file.c_str(), strerror(errno));
    return RC::IOERR;  // ?????????????????????????????????????????????
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s",
          tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // ???????????????????????????
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR(
      "Failed to rename tmp meta file (%s) to normal meta file (%s) "
      "while creating index (%s) on table (%s). "
      "system error=%d:%s",
      tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno,
      strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());

  return rc;
}

RC Table::drop_index(Trx *trx, const char *index_name) {
  RC rc = RC::SUCCESS;
  Index *index = find_index(index_name);
  if (nullptr == index) {
    rc = RC::SCHEMA_INDEX_NOT_EXIST;
    LOG_ERROR("Failed to find index (%s) on table (%s). error=%d:%s",
          index_name, name(), rc, strrc(rc));
    return rc;
  }

  std::string index_file =
    index_data_file(base_dir_.c_str(), name(), index_name);
  rc = dynamic_cast<BplusTreeIndex *>(index)->close();
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to close index file (%s) on table (%s). error=%d:%s",
          index_name, name(), rc, strrc(rc));
    return rc;
  }

  for (auto itr = indexes_.begin(); itr != indexes_.end(); itr++) {
    if (0 == strcmp((*itr)->index_meta().name(), index_name)) {
      indexes_.erase(itr);
      break;
    }
  }

  // ??????????????????
  remove(index_file.c_str());

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.remove_index(index->index_meta());

  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s",
          index_name, name(), rc, strrc(rc));
    return rc;
  }

  // ???????????????????????????
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file,
      std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s",
          tmp_file.c_str(), strerror(errno));
    return RC::IOERR;  // ?????????????????????????????????????????????
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s",
          tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // ???????????????????????????
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR(
      "Failed to rename tmp meta file (%s) to normal meta file (%s) "
      "while deleting index (%s) on table (%s). "
      "system error=%d:%s",
      tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno,
      strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("delete index (%s) on the table (%s)", index_name, name());

  return rc;
}

class RecordUpdater {
public:
  RecordUpdater(Table &table, Trx *trx, const int offset, const int len, const void *data) :
      table_(table), trx_(trx), field_offset_(offset), field_len_(len), data_(data) {}

  RC update_record(Record *record) {
    LOG_DEBUG("record to update: %p", record);
    RC rc = RC::SUCCESS;
    if (memcmp(record->data + field_offset_, data_, field_len_) == 0) {
      // ????????????
      return rc;
    }
    int record_size = table_.table_meta_.record_size();
    char *old_data = new char[record_size];
    memcpy(old_data, record->data, record_size);
    memcpy(record->data + field_offset_, data_, field_len_);
    rc = table_.update_record(trx_, record, old_data);
    if (rc == RC::SUCCESS) {
      updated_count_++;
    }
    return rc;
  }

  int updated_count() {
    return updated_count_;
  }

private:
  Table &table_;
  Trx *trx_;
  const int field_offset_;
  const int field_len_;
  const void *data_;
  int updated_count_ = 0;
};

static RC record_reader_updater_adapter(Record *record, void *context) {
  RecordUpdater &record_updater = *(RecordUpdater *) context;
  return record_updater.update_record(record);
}

RC Table::update_record(Trx *trx, const char *attribute_name, const Value *value, int condition_num,
                        const Condition conditions[], int *updated_count) {
  auto field_to_update = table_meta_.field(attribute_name);
  if (field_to_update == nullptr) {
    LOG_WARN("No such attribute name");
    return RC::SCHEMA_FIELD_MISSING;
  }

  if (!is_type_convertable(field_to_update->type(), value->type)) {
    LOG_WARN("Type of value mismatched");
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  void *data = new char[field_to_update->len()];
  // ?????????????????????
  if (convert_type(attribute_name, value->type, value->data, field_to_update->type(),
                   data, field_to_update->len(), value->is_null) != RC::SUCCESS) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  CompositeConditionFilter condition_filter;
  RC rc = condition_filter.init(*this, conditions, condition_num);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  LOG_DEBUG("field to update: name: %s, offset: %d, len: %d", field_to_update->name(), field_to_update->offset(),
            field_to_update->len());
  RecordUpdater updater(*this, trx, field_to_update->offset(), field_to_update->len(), data);
  rc = scan_record(trx, &condition_filter, -1, &updater, record_reader_updater_adapter);
  delete[] data;
  if (updated_count != nullptr) {
    *updated_count = updater.updated_count();
  }
  return rc;
}

RC Table::update_record(Trx *trx, Record *record, const char *old_data) {
  // ???????????????????????????????????? Record
  RC rc = RC::SUCCESS;
  if (trx != nullptr) {
    trx->init_trx_info(this, *record);
  }
  if (trx != nullptr) {
    rc = trx->update_record(this, record, old_data);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to log operation(update) to trx");
      return rc;
    }
  }
  rc = record_handler_->update_record(record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Update record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }
  LOG_DEBUG("Update record succeed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
  if (trx == nullptr) {
    rc = delete_entry_of_indexes(old_data, record->rid, true);
    if (rc != RC::SUCCESS) {
      LOG_PANIC("Failed to delete old index. table name=%s, rc=%d:%s", name(), rc, strrc(rc));
    }
    delete[] old_data;
    rc = insert_entry_of_indexes(record->data, record->rid);
    if (rc != RC::SUCCESS) {
      LOG_PANIC("Failed to add new index. table name=%s, rc=%d:%s", name(), rc, strrc(rc));
    }
  }
  return rc;
}


RC Table::commit_update(Trx *trx, const RID &rid, const char *old_data) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  // ????????????
  rc = delete_entry_of_indexes(old_data, record.rid, true);
  if (rc != RC::SUCCESS) {
    LOG_PANIC("Failed to delete old index. table name=%s, rc=%d:%s", name(), rc, strrc(rc));
  }
  delete[] old_data;
  rc = insert_entry_of_indexes(record.data, record.rid);
  if (rc != RC::SUCCESS) {
    LOG_PANIC("Failed to add new index. table name=%s, rc=%d:%s", name(), rc, strrc(rc));
  }
  return trx->commit_update(this, record);
}

RC Table::rollback_update(Trx *trx, const RID &rid, const char *old_data) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  // ????????????
  memcpy(record.data, old_data, table_meta_.record_size());
  const Record *record_p = &record;
  rc = record_handler_->update_record(record_p);
  if (rc != RC::SUCCESS) {
    LOG_PANIC("Failed to rollback update data. table name=%s, rc=%d:%s", name(), rc, strrc(rc));
  }
  delete[] old_data;
  return trx->rollback_update(this, record);
}

class RecordDeleter {
   public:
  RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx) {}

  RC delete_record(Record *record) {
    RC rc = RC::SUCCESS;
    rc = table_.delete_record(trx_, record);
    if (rc == RC::SUCCESS) {
      deleted_count_++;
    }
    return rc;
  }

  int deleted_count() const { return deleted_count_; }

   private:
  Table &table_;
  Trx *trx_;
  int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context) {
  RecordDeleter &record_deleter = *(RecordDeleter *)context;
  return record_deleter.delete_record(record);
}

RC Table::delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count) {
  RecordDeleter deleter(*this, trx);
  RC rc =
    scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
  if (deleted_count != nullptr) {
    *deleted_count = deleter.deleted_count();
  }
  return rc;
}

RC Table::delete_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;
 int field_num = table_meta_.field_num();
 for (int i = 0; i < field_num; i++) {
   const FieldMeta *field = table_meta_.field(i);
   if (field->type() == TEXTS) {
     int index = table_meta_.text_field_index(field->name());
     if (index == -1) {
       continue;
     }
     TextHeader text_header;
     memcpy(&text_header, record->data + field->offset(), field->len() - 1);
     if (text_header.remain_content_page_num == -1) {
       continue;
     }
     Text *text = texts_[index];
     rc = text->delete_content(text_header.remain_content_page_num);
     if (rc != RC::SUCCESS) {
       LOG_ERROR("Failed to delete text data. rc=%d:%s", rc, strrc(rc));
       return rc;
     }
   }
 }
  if (trx != nullptr) {
    rc = trx->delete_record(this, record);
  } else {
    rc = delete_entry_of_indexes(record->data, record->rid,
                   false);  // ???????????? refer to commit_delete
    if (rc != RC::SUCCESS) {
      LOG_ERROR(
        "Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
        record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
    } else {
      rc = record_handler_->delete_record(&record->rid);
    }
  }
  return rc;
}

RC Table::commit_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = delete_entry_of_indexes(record.data, record.rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
          rid.page_num, rid.slot_num, rc, strrc(rc));  // panic?
  }
  rc = record_handler_->delete_record(&rid);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

RC Table::rollback_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->rollback_delete(this, record);  // update record in place
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid,
                  bool error_on_not_exists) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const {
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}

IndexScanner *Table::find_single_index_for_scan(const DefaultConditionFilter &filter) {
  const ConDesc *field_cond_desc = nullptr;
  const ConDesc *value_cond_desc = nullptr;
  if (filter.left().is_attr && !filter.right().is_attr) {
    field_cond_desc = &filter.left();
    value_cond_desc = &filter.right();
  } else if (filter.right().is_attr && !filter.left().is_attr) {
    field_cond_desc = &filter.right();
    value_cond_desc = &filter.left();
  }
  if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
    return nullptr;
  }

  const FieldMeta *field_meta =
    table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
  if (nullptr == field_meta) {
    LOG_PANIC("Cannot find field by offset %d. table=%s",
          field_cond_desc->attr_offset, name());
    return nullptr;
  }

  const IndexMeta *index_meta =
    table_meta_.find_index_by_fields({field_meta->name()});
  if (nullptr == index_meta) {
    return nullptr;
  }

  Index *index = find_index(index_meta->name());
  if (nullptr == index) {
    return nullptr;
  }

  return index->create_scanner(filter.comp_op(),
                 (const char *)value_cond_desc->value);
}

IndexScanner *Table::find_multi_index_for_scan(const CompositeConditionFilter &filter) {
  /* ??????????????????????????????????????? */
  if (indexes_.size() == 0) {
    return nullptr;
  }
  Index *index = indexes_.front();
  const IndexMeta &index_meta = index->index_meta();
  CompOp comp_op = EQUAL_TO;
  int filter_num = filter.filter_num();

  int pkey_len = 0;
  for (const std::string & field_name : index_meta.fields()) {
    /* ???????????????????????? filter ??????????????????????????????????????? */
    const FieldMeta *field = table_meta_.field(field_name.c_str());
    if (field == nullptr) {
      return nullptr;
    }
    pkey_len += field->len();
  }

  int offset = 0;
  char *pkey = new char[pkey_len];
  memset(pkey, 0, pkey_len);
  for (const std::string & field_name : index_meta.fields()) {
    /* ???????????????????????? filter ??????????????????????????????????????? */
    bool find = false;
    for (int i = 0; i < filter_num; i++) {
      const DefaultConditionFilter *default_condition_filter =
        dynamic_cast<const DefaultConditionFilter *>(&filter.filter(i));
      if (nullptr == default_condition_filter) {
        delete[] pkey;
        return nullptr;
      }
      const ConDesc *field_cond_desc = nullptr;
      const ConDesc *value_cond_desc = nullptr;
      if (default_condition_filter->left().is_attr && !default_condition_filter->right().is_attr) {
        field_cond_desc = &default_condition_filter->left();
        value_cond_desc = &default_condition_filter->right();
      } else if (default_condition_filter->right().is_attr && !default_condition_filter->left().is_attr) {
        field_cond_desc = &default_condition_filter->right();
        value_cond_desc = &default_condition_filter->left();
      }
      if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
        continue;
      }
      const FieldMeta *field_cond_meta =
        table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
      if (nullptr == field_cond_meta) {
        LOG_PANIC("Cannot find field by offset %d. table=%s",
              field_cond_desc->attr_offset, name());
        return nullptr;
      }
      if (0 == strcmp(field_cond_meta->name(), field_name.c_str())) {
        find = true;
        if (value_cond_desc->is_null) {
          memset(pkey + offset, 0, field_cond_meta->len());
          *(pkey + offset + field_cond_meta->len() - 1) = 1;
        } else {
          memcpy(pkey + offset, value_cond_desc->value, field_cond_meta->len() - 1); // ???????????? null ????????????
        }
        offset += field_cond_meta->len();
        if (comp_op == EQUAL_TO) {
          comp_op = default_condition_filter->comp_op();
        }
        break;
      }
    }
    if (!find) {
      delete[] pkey;
      return nullptr;
    }
  }
  IndexScanner *scanner = index->create_scanner(comp_op, pkey);
  delete[] pkey;
  return scanner;
}

IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter) {
  /* ?????????????????????????????????????????????????????????????????????????????????????????? */
  if (nullptr == filter) {
    return nullptr;
  }

  // remove dynamic_cast
  const DefaultConditionFilter *default_condition_filter =
    dynamic_cast<const DefaultConditionFilter *>(filter);
  if (default_condition_filter != nullptr) {
    return find_single_index_for_scan(*default_condition_filter);
  }

  const CompositeConditionFilter *composite_condition_filter =
    dynamic_cast<const CompositeConditionFilter *>(filter);
  if (composite_condition_filter != nullptr) {
    /* ??????????????????????????? */
    int filter_num = composite_condition_filter->filter_num();
    for (int i = 0; i < filter_num; i++) {
      IndexScanner *scanner =
        find_index_for_scan(&composite_condition_filter->filter(i));
      if (scanner != nullptr) {
        return scanner;  // ???????????????????????????????????????????????????=
      }
    }
    /* ??????????????????????????? */
    IndexScanner *scanner = find_multi_index_for_scan(*composite_condition_filter);
    if (scanner != nullptr) {
      return scanner;
    }
  }
  return nullptr;
}

RC Table::sync() {
  RC rc = data_buffer_pool_->flush_all_pages(file_id_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to flush table's data pages. table=%s, rc=%d:%s",
          name(), rc, strrc(rc));
    return rc;
  }

  for (Text *text: texts_) {
    rc = text->sync();
    if (rc != RC::SUCCESS) {
        LOG_ERROR(
        "Failed to flush text's pages. table=%s, text field=%s, rc=%d:%s",
        name(), text->meta().name(), rc, strrc(rc));
      return rc; 
    }
  }

  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR(
        "Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
        name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}

RC Table::create_text_field(const char *base_dir, const char *text_field_name) {
  if (text_field_name == nullptr || common::is_blank(text_field_name)) {
    return RC::INVALID_ARGUMENT;
  }
  TextFieldMeta new_text_field;
  RC rc = new_text_field.init(text_field_name);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  Text *text = new Text;
  std::string text_file = text_data_file(base_dir, name(), text_field_name);
  rc = text->create(text_file.c_str(), new_text_field);
  if (rc != RC::SUCCESS) {
    delete text;
    LOG_ERROR("Failed to create text field. file name=%s, rc=%d:%s", text_file.c_str(), rc, strrc(rc));
    return rc;
  }
  texts_.push_back(text);
  table_meta_.add_text_field(new_text_field);
  return RC::SUCCESS;
}

RC Table::remove_text_files() {
  for (int i = 0; i < table_meta_.text_field_num(); i++) {
    texts_[i]->close();
    std::string text_file = text_data_file(base_dir_.c_str(), name(), table_meta_.text_field(i)->name());
    remove(text_file.c_str());
  }
  return RC::SUCCESS;
}