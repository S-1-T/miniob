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
// Created by Wangyunlai on 2021/5/14.
//

#include <ctime>
#include <iostream>

#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "common/log/log.h"

Tuple::Tuple(const Tuple &other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {
}

Tuple & Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value) {
  add(new IntValue(value));
}

void Tuple::add(float value) {
  add(new FloatValue(value));
}

void Tuple::add(time_t value) {
  add(new DateValue(value));
}

void Tuple::add(const char *s, int len) {
  add(new StringValue(s, len));
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema) {
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add(field_meta->type(), table_name, field_meta->name());
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name);
}

void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

void TupleSchema::print(std::ostream &os, bool multi_table) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    if (multi_table) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }

  if (multi_table) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name() << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_){
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::merge(Tuple &&tuple, std::vector<AggregationType> aggregation_types) {
  // 在未实现 GROUP BY 语句之前，只要存在 None 的 aggregation_type，就说明是一个无聚合的查询
  if (aggregation_types[0] == None) {
    tuples_.emplace_back(std::move(tuple));
    return;
  }
  Tuple new_tuple;
  int value_idx = 0;
  const std::vector<std::shared_ptr<TupleValue>> new_values = tuple.values();
  // 第一次计算，首先进行初始化
  if (tuples_.empty()) {
    for (std::shared_ptr<TupleValue> new_value: new_values) {
      int cur_value_idx = value_idx++;
      AggregationType aggregation_type = aggregation_types[cur_value_idx];
      switch (aggregation_type) {
      case CountAggregate: {
          int count = 1;
          new_tuple.add(count);
      }
      break;
      case SumAggregate:
      case MinAggregate:
      case MaxAggregate: {
          new_tuple.add(new_value);
      }
      break;
      default: {
        LOG_PANIC("Unsupported aggregation type. type=%d", aggregation_type);
      }
      }
    }
    tuples_.emplace_back(std::move(new_tuple));
    return;
  }
  // 聚合函数的 Merge 计算
  for (std::shared_ptr<TupleValue> new_value: new_values) {
    int cur_value_idx = value_idx++;
    // 聚合运算的每一个阶段，tuples_ 都只含有一个 Tuple
    const std::shared_ptr<TupleValue> old_value = tuples_[0].get_pointer(cur_value_idx);
    AggregationType aggregation_type = aggregation_types[cur_value_idx];
    switch (aggregation_type) {
    case CountAggregate: {
      old_value.get()->add(IntValue(1));
      new_tuple.add(old_value);
    }
    break;
    case SumAggregate: {
      old_value.get()->add(*new_value.get());
      new_tuple.add(old_value);
    }
    break;
    case MinAggregate: {
      if (new_value.get()->compare(*old_value.get()) < 0)
        new_tuple.add(new_value);
      else
        new_tuple.add(old_value);
    }
    break;
    case MaxAggregate: {
      if (new_value.get()->compare(*old_value.get()) > 0)
        new_tuple.add(new_value);
      else
        new_tuple.add(old_value);
    }
    break;
    default: {
      LOG_PANIC("Unsupported aggregation type. type=%d", aggregation_type);
    }
    }
  }
  // 判断是否需要存入新的 Merge 计算结果
  if (new_tuple.size() != 0) {
    tuples_.pop_back();
    tuples_.emplace_back(std::move(new_tuple));
  }
  return;
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print(std::ostream &os, bool multi_table) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print(os, multi_table);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}

void TupleSet::set_schema(const TupleSchema &schema) {
  schema_ = schema;
}

const TupleSchema &TupleSet::get_schema() const {
  return schema_;
}

bool TupleSet::is_empty() const {
  return tuples_.empty();
}

int TupleSet::size() const {
  return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
  return tuples_[index];
}

const std::vector<Tuple> &TupleSet::tuples() const {
  return tuples_;
}

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set, std::vector<AggregationType> *aggregation_types) :
  table_(table), tuple_set_(tuple_set), aggregation_types_(aggregation_types) {
}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);
    switch (field_meta->type()) {
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add(value);
      }
      break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        tuple.add(value);
      }
      break;
      case DATES: {
        time_t value = *(time_t *)(record + field_meta->offset());
        tuple.add(value);
      }
      break;
      case CHARS: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      }
      break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.merge(std::move(tuple), *aggregation_types_);
}
