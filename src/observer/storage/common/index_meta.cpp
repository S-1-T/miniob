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
// Created by wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAMES("field_names");
const static Json::StaticString FIELD_IS_UNIQUE("is_unique");

RC IndexMeta::init(const char *name, const std::vector<FieldMeta> &fields, bool is_unique) {
  if (nullptr == name || common::is_blank(name)) {
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  fields_.clear();
  for (auto & field : fields) {
    fields_.emplace_back(field.name());
  }
  is_unique_ = is_unique;
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[FIELD_NAME] = name_;
  Json::Value fields_value;
  for (auto field : fields_) {
    fields_value.append(field);
  }
  json_value[FIELD_FIELD_NAMES] = fields_value;
  json_value[FIELD_IS_UNIQUE] = is_unique_;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index) {
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &fields_value = json_value[FIELD_FIELD_NAMES];
  const Json::Value &is_unique = json_value[FIELD_IS_UNIQUE];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!fields_value.isArray()) {
    LOG_ERROR("Invalid index meta. fields is not array. json value=%s",
      fields_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!is_unique.isBool()) {
    LOG_ERROR("Unique property of index [%s] is not a string. json value=%s",
              name_value.asCString(), is_unique.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  int field_num = fields_value.size();
  std::vector<FieldMeta> fields;
  for (int i = 0; i < field_num; i++) {
    const Json::Value &field_name = fields_value[i];
    if (!field_name.isString()) {
      LOG_ERROR("field name is not a string. json value=%s", name_value.toStyledString().c_str());
      return RC::GENERIC_ERROR;
    }
    const FieldMeta *field = table.field(field_name.asCString());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_name.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.push_back(*field);
  }

  return index.init(name_value.asCString(), fields, is_unique.asBool());
}

const char *IndexMeta::name() const {
  return name_.c_str();
}

const std::vector<std::string> &IndexMeta::fields() const {
  return fields_;
}

bool IndexMeta::is_unique() const {
  return is_unique_;
}

void IndexMeta::desc(std::ostream &os) const {
  os << "index name=" << name_;
  os << ", field=";
  if (fields_.size() == 1) {
    os << fields_.front();
  } else {
    os << "(";
    for (int i = 0; i < fields_.size() - 1; i++) {
      os << fields_[i] << ", ";
    }
    os << fields_.back() << ")";
  }
  os << " is_unique=" << is_unique_;
}