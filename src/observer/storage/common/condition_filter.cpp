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
// Created by Wangyunlai on 2021/5/7.
//

#include <cmath>
#include <sql/executor/tuple.h>
#include <sql/executor/execute_stage.h>
#include <storage/default/default_handler.h>

#include "condition_filter.h"

#include "common/log/log.h"
#include "record_manager.h"
#include "storage/common/table.h"
#include "storage/common/type/date.h"
#include "storage/common/type/convert.h"

using namespace common;

ConditionFilter::~ConditionFilter() {}

DefaultConditionFilter::DefaultConditionFilter() {
  left_.is_attr = false;
  left_.attr_length = 0;
  left_.attr_offset = 0;
  left_.value = nullptr;

  right_.is_attr = false;
  right_.attr_length = 0;
  right_.attr_offset = 0;
  right_.value = nullptr;
}
DefaultConditionFilter::~DefaultConditionFilter() {}

RC DefaultConditionFilter::init(const ConDesc &left, const ConDesc &right,
                                AttrType attr_type, AttrType type_right, CompOp comp_op) {
  if (attr_type < CHARS || attr_type > TUPLESET || type_right < CHARS || type_right > TUPLESET) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d %d",
              attr_type, type_right);
    return RC::INVALID_ARGUMENT;
  }

  if (comp_op < EQUAL_TO || comp_op >= NO_OP) {
    LOG_ERROR("Invalid condition with unsupported compare operation: %d",
              comp_op);
    return RC::INVALID_ARGUMENT;
  }

  left_ = left;
  right_ = right;
  attr_type_ = attr_type;
  type_right_ = type_right;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}

RC DefaultConditionFilter::init(Table &table, const Condition &condition, const char* db) {
  const TableMeta &table_meta = table.table_meta();
  ConDesc left;
  ConDesc right;

  AttrType type_left = UNDEFINED;
  AttrType type_right = UNDEFINED;

  if (1 == condition.left_is_attr) {
    left.is_attr = true;
    const FieldMeta *field_left =
        table_meta.field(condition.left_attr.attribute_name);

    if (field_left == nullptr) {
      Table * table = DefaultHandler::get_default().find_table(db, condition.left_attr.relation_name);
      field_left = table->table_meta().field(condition.left_attr.attribute_name);
    }

    left.attr_length = field_left->len();
    left.attr_offset = field_left->offset();

    left.value = nullptr;

    type_left = field_left->type();
    left.attr_type = type_left;
    left.rel_name = condition.left_attr.relation_name;
    left.attr_name = condition.left_attr.attribute_name;
  } else {
    left.is_attr = false;
    left.value = condition.left_value.data;  // 校验type 或者转换类型

    if (0 == condition.left_is_attr) {
      type_left = condition.left_value.type;
    } else {
      Selects* left_select = (Selects*)condition.left_value.data;
      RelAttr left_attr = left_select->attributes[0];
      Table * subquery_table = DefaultHandler::get_default().find_table(db, left_attr.relation_name);
      type_left = subquery_table->table_meta().field(left_attr.attribute_name)->type();
    }

    right.attr_type = condition.left_value.type;

    left.attr_length = 0;
    left.attr_offset = 0;
    left.is_null = condition.left_value.is_null;
  }

  if (1 == condition.right_is_attr) {
    right.is_attr = true;
    const FieldMeta *field_right =
        table_meta.field(condition.right_attr.attribute_name);
    if (field_right == nullptr) {
      Table * table = DefaultHandler::get_default().find_table(db, condition.right_attr.relation_name);
      field_right = table->table_meta().field(condition.right_attr.attribute_name);
      right.rel_name = condition.right_attr.relation_name;
      right.attr_name = condition.right_attr.attribute_name;
    }
    right.attr_length = field_right->len();
    right.attr_offset = field_right->offset();
    type_right = field_right->type();

    right.value = nullptr;
    right.attr_type = type_right;
    right.rel_name = condition.right_attr.relation_name;
    right.attr_name = condition.right_attr.attribute_name;
  } else {
    right.is_attr = false;
    right.value = condition.right_value.data;

    if (0 == condition.right_is_attr) {
      type_right = condition.right_value.type;
    } else {
      Selects* right_select = (Selects*)condition.right_value.data;
      RelAttr right_attr = right_select->attributes[0];
      Table * subquery_table = DefaultHandler::get_default().find_table(db, right_attr.relation_name);
      type_right = subquery_table->table_meta().field(right_attr.attribute_name)->type();
    }

    right.attr_type = condition.right_value.type;

    right.attr_length = 0;
    right.attr_offset = 0;
    right.is_null = condition.right_value.is_null;
  }

  // 校验和转换
  if (!is_type_convertable(type_left, type_right)) {
    LOG_WARN(
        "Two values' types incompatible, left: %d, right: %d",
        type_left, type_right);
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  if (type_left == DATES && type_right == CHARS) {
    type_right = DATES;
    right.attr_type = DATES;
    if (right.value != nullptr) {
      try {
        Date date = Date(static_cast<char *>(right.value));
        time_t date_time_t = date.get_inner_date_time_t();
        memcpy(right.value, &date_time_t, sizeof(date_time_t));
      } catch (const char *e) {
        LOG_WARN(
            "Invalid right value data to convert into a Date type. "
            "e=%s",
            e);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
  } else if (type_left == CHARS && type_right == DATES) {
    type_left = DATES;
    left.attr_type = DATES;
    if (left.value != nullptr) {
      try {
        Date date = Date(static_cast<char *>(left.value));
        time_t date_time_t = date.get_inner_date_time_t();
        memcpy(left.value, &date_time_t, sizeof(date_time_t));
      } catch (const char *e) {
        LOG_WARN(
          "Invalid right value data to convert into a Date type. "
          "e=%s",
          e);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
  }
  return init(left, right, type_left, type_right, condition.comp);
}

bool DefaultConditionFilter::filter(const Record &rec) const {
  char *left_value = nullptr;
  char *right_value = nullptr;
  bool left_is_null = false;
  bool right_is_null = false;
  if (left_.is_attr) {  // value
    left_value = (char *)(rec.data + left_.attr_offset);
    left_is_null = (bool)(left_value[left_.attr_length - 1]);
  } else {
    left_value = (char *)left_.value;
    left_is_null = left_.is_null;
  }

  if (right_.is_attr) {
    right_value = (char *)(rec.data + right_.attr_offset);
    right_is_null = (bool)(right_value[right_.attr_length - 1]);
  } else {
    right_value = (char *)right_.value;
    right_is_null = right_.is_null;
  }
  // NULL 特殊处理
  if (left_is_null || right_is_null) {
    switch (comp_op_) {
      case IS:
        return left_is_null == right_is_null;
      case IS_NOT:
        return left_is_null != right_is_null;
      default:
        return false;
    }
  }

  int cmp_result = 0;
  if (left_.attr_type != TUPLESET && right_.attr_type != TUPLESET) {
    cmp_result = get_cmp_result(left_value, right_value);
  } else {
    // 根据record生成Tuple

    // 填充子查询内容 -> 直接再ConSec加字段

    // 执行子查询 -> 返回的TupleSet的存储问题

    // 比较
    if (right_.attr_type == TUPLESET) {
      TupleSet* tupleSet = reinterpret_cast<TupleSet*>(right_value);
      TupleValue* left_data = getTuple(attr_type_, left_value);
      for (int i=0; i<tupleSet->size(); i++) {
        if (left_data->compare_with_op(tupleSet->get(i).get(0), comp_op_)) {
          delete left_data;
          return comp_op_ != NOT_IN_OP;
        }
      }
      delete left_data;
    } else {
      TupleSet* tupleSet = reinterpret_cast<TupleSet*>(left_value);
      TupleValue* right_data = getTuple(type_right_, right_value);
      for (int i=0; i<tupleSet->size(); i++) {
        if (tupleSet->get(i).get(0).compare_with_op(*right_data, comp_op_)) {
          delete right_data;
          return comp_op_ != NOT_IN_OP;
        }
      }
      delete right_data;
    }

    return comp_op_ == NOT_IN_OP;
  }

  switch (comp_op_) {
    case EQUAL_TO:
      return 0 == cmp_result;
    case LESS_EQUAL:
      return cmp_result <= 0;
    case NOT_EQUAL:
      return cmp_result != 0;
    case LESS_THAN:
      return cmp_result < 0;
    case GREAT_EQUAL:
      return cmp_result >= 0;
    case GREAT_THAN:
      return cmp_result > 0;
    case IN_OP:
      return cmp_result > 0;
    default:
      break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result;  // should not go here
}

TupleValue *DefaultConditionFilter::getTuple(AttrType attr_type, char* left_value) const{
  switch (attr_type) {
    case CHARS: {  // 字符串都是定长的，直接比较
      return dynamic_cast<TupleValue *>(new StringValue(left_value));
    } break;
    case INTS: {
      return dynamic_cast<TupleValue *>(new IntValue((*(int *) left_value)));
    } break;
    case FLOATS: {
      return dynamic_cast<TupleValue *>(new FloatValue(*(float *)left_value));
    } break;
    case DATES: {
      return dynamic_cast<TupleValue *>(new DateValue(*(time_t *)left_value));
    } break;
    default: {
    }
  }

  return nullptr;
}

int DefaultConditionFilter::get_cmp_result(char *left_value, char *right_value) const {
  int cmp_result = 0;
  // 这里的 attr_type_ 是 left_value 的类型
  switch (attr_type_) {
    case CHARS: {  // 字符串都是定长的，直接比较
      // 按照C字符串风格来定
      cmp_result = strcmp(left_value, right_value);
    } break;
    case INTS: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      if (right_.attr_type == FLOATS) {
        int left = *(int *) left_value;
        float right = *(float *) right_value;
        float result = (float)left - right;
        if (result <= 1e-6 && result >= -1e-6) {
          cmp_result = 0;
        } else if (result > 0) {
          cmp_result = 1;
        } else {
          cmp_result = -1;
        }
      } else {
        int left = *(int *) left_value;
        int right = *(int *) right_value;
        cmp_result = left - right;
      }
    } break;
    case FLOATS: {
      float left = *(float *)left_value;
      float right = 0;
      if (right_.attr_type == INTS) {
        right = (float)(*(int *)right_value);
      } else {
        right = *(float *)right_value;
      }
      LOG_DEBUG("left: %f, right: %f", left, right);
      float result = left - right;
      if (result <= 1e-6 && result >= -1e-6) {
        cmp_result = 0;
      } else if (result > 0) {
        cmp_result = 1;
      } else {
        cmp_result = -1;
      }
      LOG_DEBUG("cmp result: %d", cmp_result);
    } break;
    case DATES: {
      time_t left = *(time_t *)left_value;
      time_t right = *(time_t *)right_value;
      cmp_result = (int)(left - right);
    } break;
    default: {
    }
  }
  return cmp_result;
}

CompositeConditionFilter::~CompositeConditionFilter() {
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[],
                                  int filter_num, bool own_memory) {
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}
RC CompositeConditionFilter::init(const ConditionFilter *filters[],
                                  int filter_num) {
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table &table, const Condition *conditions,
                                  int condition_num) {
  if (condition_num == 0) {
    return RC::SUCCESS;
  }
  if (conditions == nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  ConditionFilter **condition_filters = new ConditionFilter *[condition_num];
  for (int i = 0; i < condition_num; i++) {
    DefaultConditionFilter *default_condition_filter =
        new DefaultConditionFilter();
    rc = default_condition_filter->init(table, conditions[i]);
    if (rc != RC::SUCCESS) {
      delete default_condition_filter;
      for (int j = i - 1; j >= 0; j--) {
        delete condition_filters[j];
        condition_filters[j] = nullptr;
      }
      delete[] condition_filters;
      condition_filters = nullptr;
      return rc;
    }
    condition_filters[i] = default_condition_filter;
  }
  return init((const ConditionFilter **)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record &rec) const {
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}
