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
// Created by Wangyunlai on 2021/5/12.
//

#ifndef __OBSERVER_STORAGE_COMMON_TABLE_H__
#define __OBSERVER_STORAGE_COMMON_TABLE_H__

#include "storage/common/table_meta.h"

class DiskBufferPool;
class RecordFileHandler;
class ConditionFilter;
class CompositeConditionFilter;
class DefaultConditionFilter;
struct Record;
struct RID;
class Index;
class IndexScanner;
class RecordDeleter;
class Trx;
class Text;

class Table {
public:
  Table();
  ~Table();

  /**
   * 创建一个表
   * @param path 元数据保存的文件(完整路径)
   * @param name 表名
   * @param base_dir 表数据存放的路径
   * @param attribute_count 字段个数
   * @param attributes 字段
   */
  RC create(const char *path, const char *name, const char *base_dir, int attribute_count, const AttrInfo attributes[]);

  /**
   * 打开一个表
   * @param meta_file 保存表元数据的文件完整路径
   * @param base_dir 表所在的文件夹，表记录数据文件、索引数据文件存放位置
   */
  RC open(const char *meta_file, const char *base_dir);
  RC close();

  RC insert_record(Trx *trx, int value_num, const Value *values);
  RC insert_records(Trx *trx, int tuple_num, const InsertTuple *tuples);
  RC update_record(Trx *trx, const char *attribute_name, const Value *value, int condition_num, const Condition conditions[], int *updated_count);
  RC delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count);

  RC scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, void (*record_reader)(const char *data, void *context));

  RC create_index(Trx *trx, const char *index_name, const char *attribute_names[], size_t attr_num, bool is_unique);
  RC drop_index(Trx *trx, const char *index_name);

public:
  const char *name() const;

  const TableMeta &table_meta() const;

  RC sync();

public:
  RC commit_insert(Trx *trx, const RID &rid);
  RC commit_delete(Trx *trx, const RID &rid);
  RC commit_update(Trx *trx, const RID &rid, const char *old_data);
  RC rollback_insert(Trx *trx, const RID &rid);
  RC rollback_delete(Trx *trx, const RID &rid);
  RC rollback_update(Trx *trx, const RID &rid, const char *old_data);
  RC remove_text_files();
  Text *text(int index);

private:
  RC scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, RC (*record_reader)(Record *record, void *context));
  RC scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter, int limit, void *context, RC (*record_reader)(Record *record, void *context));
  IndexScanner *find_index_for_scan(const ConditionFilter *filter);
  IndexScanner *find_single_index_for_scan(const DefaultConditionFilter &filter);
  IndexScanner *find_multi_index_for_scan(const CompositeConditionFilter &filter);

  RC convert_type(const char *field_name, AttrType src_type, void *src_data, AttrType dest_type, void *dest_data, int len, bool is_null);

  RC insert_record(Trx *trx, Record *record);
  RC delete_record(Trx *trx, Record *record);
  RC update_record(Trx *trx, Record *record, const char *old_data);

  RC create_text_field(const char *base_dir, const char *name);
private:
  friend class RecordUpdater;
  friend class RecordDeleter;

  RC insert_entry_of_indexes(const char *record, const RID &rid);
  RC delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists);
private:
  RC init_record_handler(const char *base_dir);
  RC make_record(int value_num, const Value *values, char * &record_out);

private:
  Index *find_index(const char *index_name) const;

private:
  std::string             base_dir_;
  TableMeta               table_meta_;
  DiskBufferPool *        data_buffer_pool_; /// 数据文件关联的buffer pool
  int                     file_id_;
  RecordFileHandler *     record_handler_;   /// 记录操作
  std::vector<Index *>    indexes_;
  std::vector<Text *>     texts_;
};

#endif // __OBSERVER_STORAGE_COMMON_TABLE_H__