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

#include "sql/executor/tuple.h"

#include <ctime>
#include <iostream>
#include <algorithm>

#include "common/log/log.h"
#include "storage/common/table.h"

Tuple::Tuple(const Tuple &other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {}

Tuple &Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);

  return *this;
}

Tuple &Tuple::operator=(Tuple &other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  auto &values = other.values();
  for (auto v: values) {
    values_.emplace_back(v);
  }
  return *this;
}

Tuple::~Tuple() {}

// add (Value && value)
void Tuple::add(TupleValue *value) { values_.emplace_back(value); }
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value, AggregationType aggregation_type, bool is_null) {
  add(new IntValue(value, aggregation_type, is_null));
}

void Tuple::add(float value, AggregationType aggregation_type, bool is_null) {
  add(new FloatValue(value, aggregation_type, is_null));
}

void Tuple::add(time_t value, AggregationType aggregation_type, bool is_null) {
  add(new DateValue(value, aggregation_type, is_null));
}

void Tuple::add(const char *s, int len, AggregationType aggregation_type, bool is_null) {
  add(new StringValue(s, len, aggregation_type, is_null));
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
      schema.add(field_meta->type(), table_name, field_meta->name(),
                 AggregationType::None);
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name,
                      const char *field_name,
                      const AggregationType aggregation_type) {
  fields_.emplace_back(type, table_name, field_name, aggregation_type);
}

void TupleSchema::add_if_not_exists(AttrType type, const char *table_name,
                                    const char *field_name) {
  for (const auto &field : fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name, AggregationType::None);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field : other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name,
                                const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
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
    const AggregationType aggregation_type = iter->aggregation_type();
    if (aggregation_type != None)
      os << aggregation_type_to_string(aggregation_type) << "(";
    if (multi_table) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name();
    if (aggregation_type != None) os << ")";
    os << " | ";
  }
  const AggregationType aggregation_type = fields_.back().aggregation_type();
  if (aggregation_type != None)
    os << aggregation_type_to_string(aggregation_type) << "(";
  if (multi_table) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name();
  if (aggregation_type != None) os << ")";
  os << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other)
    : tuples_(std::move(other.tuples_)), schema_(other.schema_) {
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

void TupleSet::merge(Tuple &&tuple) {
  if (tuples_.empty()) {
    tuples_.emplace_back(std::move(tuple));
    return;
  }
  // 聚合运算的每一个阶段，tuples_ 都只含有一个 Tuple
  const std::vector<std::shared_ptr<TupleValue>> old_values =
      tuples_[0].values();
  int value_idx = 0;
  for (std::shared_ptr<TupleValue> old_value : old_values) {
    // 正常扫表而非聚合运算，直接将 tuple 存入
    if (old_value->aggregation_type() == None) {
      tuples_.emplace_back(std::move(tuple));
      return;
    }
    // 聚合函数的 Merge 计算
    old_value->merge(tuple.get(value_idx++));
  }
  return;
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::sort(const OrderBy orders[], size_t order_num) {
  std::sort(
      tuples_.begin(),
      tuples_.end(),
      [&](Tuple &t1, Tuple &t2) {
        if (t1.size() == 0 || t2.size() == 0) {
          return false;
        }
        for (int i = order_num - 1; i >= 0; i--) {
          const OrderBy &order = orders[i];
          const RelAttr &attr = order.attr;
          int idx = schema_.index_of_field(attr.relation_name, attr.attribute_name);
          const TupleValue &t1_v = t1.get(idx);
          const TupleValue &t2_v = t2.get(idx);
          int cmp_result = t1_v.compare(t2_v);
          if (cmp_result == 0) {
            continue;
          }
          if (order.type == OrderType::AscOrder) {
            return cmp_result < 0;
          } else {
            return cmp_result > 0;
          }
        }
        return true;
      }
  );
}

void TupleSet::print(std::ostream &os, bool multi_table) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print(os, multi_table);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    int output_size = schema_.fields().size();
    for (int i = 0; i < output_size - 1; i++) {
      const auto &value = values[i];
      value->to_string(os);
      os << " | ";
    }
    values[output_size - 1]->to_string(os);
    os << std::endl;
  }
}

void TupleSet::set_schema(const TupleSchema &schema) { schema_ = schema; }

const TupleSchema &TupleSet::get_schema() const { return schema_; }

bool TupleSet::is_empty() const { return tuples_.empty(); }

int TupleSet::size() const { return tuples_.size(); }

const Tuple &TupleSet::get(int index) const { return tuples_[index]; }

const std::vector<Tuple> &TupleSet::tuples() const { return tuples_; }

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set)
    : table_(table), tuple_set_(tuple_set) {}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    if (field_meta == nullptr && field.aggregation_type() != None) {
      field_meta = table_meta.field(0);
    }
    assert(field_meta != nullptr);
    const AggregationType aggregation_type = field.aggregation_type();
    const bool is_null = (bool)((char *)record[field_meta->offset() + field_meta->len() - 1]);
    switch (field_meta->type()) {
      case INTS: {
        int value = *(int *)(record + field_meta->offset());
        tuple.add(value, aggregation_type, is_null);
      } break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        tuple.add(value, aggregation_type, is_null);
      } break;
      case DATES: {
        time_t value = *(time_t *)(record + field_meta->offset());
        tuple.add(value, aggregation_type, is_null);
      } break;
      case CHARS: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s), aggregation_type, is_null);
      } break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.merge(std::move(tuple));
}
