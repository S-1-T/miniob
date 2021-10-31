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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <cstdio>
#include <ctime>
#include <ostream>
#include <string>

#include "common/log/log.h"
#include "sql/parser/parse.h"

const char *format_double(double value);

class TupleValue {
 public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream &os) const = 0;
  virtual void merge(const TupleValue &other) = 0;
  virtual int compare(const TupleValue &other) const = 0;
  virtual bool compare_with_op(const TupleValue &other, CompOp comp) const {
    // NULL 与任何值比较都是 false，除非是 IS 和 IS NOT
    if (is_null() || other.is_null()) {
      switch (comp) {
        case IS:
          return is_null() == other.is_null();
        case IS_NOT:
          return is_null() != other.is_null();
        default:
          return false;
      }
    }
    auto cmp_result = compare(other);
    switch (comp) {
      case IN_OP:
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
      default:
        break;
    }
    return cmp_result == 0;
  }
  virtual AttrType type() const = 0;
  virtual bool is_null() const = 0;
  AggregationType aggregation_type() const { return aggregation_type_; }

 protected:
  int count = 1;
  AggregationType aggregation_type_ = None;
};

class IntValue : public TupleValue {
 public:
  explicit IntValue(int value) : value_(value), avg_(value) {}
  explicit IntValue(int value, AggregationType aggregation_type, bool is_null)
      : value_(value), avg_(value), is_null_(is_null) {
    aggregation_type_ = aggregation_type;
  }

  void to_string(std::ostream &os) const override {
    switch (aggregation_type_) {
      case CountAggregate: {
        if (is_null_) {
          os << 0;
        } else {
          os << count;
        }
      } break;
      case AvgAggregate: {
        if (is_null_) {
          os << "NULL";
        } else {
          const char *out = format_double(avg_);
          os << out;
          delete[] out;
        }
      } break;
      default: {
        if (is_null_) {
          os << "NULL";
        } else {
          os << value_;
        }
      }
    }
  }

  void merge(const TupleValue &other) override {
    // NULL 不计入聚合
    if (other.is_null()) {
      return;
    }
    is_null_ = false;
    const IntValue &int_other = (const IntValue &)other;
    switch (aggregation_type_) {
      case CountAggregate: {
        count++;
      } break;
      case SumAggregate: {
        value_ = value_ + int_other.value_;
      } break;
      case AvgAggregate: {
        int pre_count = count++;
        avg_ = (avg_ * pre_count + int_other.value_) / count;
      } break;
      case MaxAggregate: {
        if (compare(int_other) < 0) value_ = int_other.value_;
      } break;
      case MinAggregate: {
        if (compare(int_other) > 0) value_ = int_other.value_;
      }
      default: {
      }
    }
  }

  int compare(const TupleValue &other) const override {
    const IntValue &int_other = (const IntValue &)other;
    return value_ - int_other.value_;
  }

  AttrType type() const override {
    return INTS;
  }

  bool is_null() const override {
    return is_null_;
  }

private:
  int value_;
  double avg_ = 0;
  bool is_null_ = false;
};

class FloatValue : public TupleValue {
 public:
  explicit FloatValue(float value) : value_(value), avg_(value) {}
  explicit FloatValue(float value, AggregationType aggregation_type, bool is_null)
      : value_(value), avg_(value), is_null_(is_null) {
    aggregation_type_ = aggregation_type;
  }

  void to_string(std::ostream &os) const override {
    switch (aggregation_type_) {
      case CountAggregate: {
        if (is_null_) {
          os << 0;
        } else {
          os << count;
        }
      } break;
      case AvgAggregate: {
        if (is_null_) {
          os << "NULL";
        } else {
          const char *out = format_double(avg_);
          os << out;
          delete[] out;
        }
      } break;
      default: {
        if (is_null_) {
          os << "NULL";
        } else {
          const char *out = format_double(double(value_));
          os << out;
          delete[] out;
        }
      }
    }
  }

  void merge(const TupleValue &other) override {
    // NULL 不计入聚合
    if (other.is_null()) {
      return;
    }
    is_null_ = false;
    const FloatValue &float_other = (const FloatValue &)other;
    switch (aggregation_type_) {
      case CountAggregate: {
        count++;
      } break;
      case SumAggregate: {
        value_ = value_ + float_other.value_;
      } break;
      case AvgAggregate: {
        int pre_count = count++;
        avg_ = (avg_ * pre_count + float_other.value_) / count;
      } break;
      case MaxAggregate: {
        if (compare(float_other) < 0) value_ = float_other.value_;
      } break;
      case MinAggregate: {
        if (compare(float_other) > 0) value_ = float_other.value_;
      }
      default: {
      }
    }
  }

  int compare(const TupleValue &other) const override {
    const FloatValue &float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (result > 0) {  // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
  }

  AttrType type() const override {
    return FLOATS;
  }

  bool is_null() const override {
    return is_null_;
  }
private:
  float value_;
  double avg_ = 0;
  bool is_null_ = false;
};

class DateValue : public TupleValue {
 public:
  explicit DateValue(time_t value) : value_(value) {}
  explicit DateValue(time_t value, AggregationType aggregation_type, bool is_null)
      : value_(value), is_null_(is_null) {
    aggregation_type_ = aggregation_type;
  }

  void to_string(std::ostream &os) const override {
    switch (aggregation_type_) {
      case CountAggregate: {
        if (is_null_) {
          os << 0;
        } else {
          os << count;
        }
      } break;
      default: {
        if (is_null_) {
          os << "NULL";
        } else {
          struct tm *ptm = std::localtime(&value_);
          char buffer[32];
          strftime(buffer, 32, "%Y-%m-%d", ptm);
          os << buffer;
        }
      }
    }
  }

  void merge(const TupleValue &other) override {
    // NULL 不计入聚合
    if (other.is_null()) {
      return;
    }
    is_null_ = false;
    const DateValue &date_other = (const DateValue &)other;
    switch (aggregation_type_) {
      case CountAggregate: {
        count++;
      } break;
      case MaxAggregate: {
        if (compare(date_other) < 0) value_ = date_other.value_;
      } break;
      case MinAggregate: {
        if (compare(date_other) > 0) value_ = date_other.value_;
      }
      default: {
      }
    }
  }

  int compare(const TupleValue &other) const override {
    const DateValue &date_other = (const DateValue &)other;
    double diff_seconds = difftime(value_, date_other.value_);
    if (diff_seconds > 0) {
      return 1;
    }
    if (diff_seconds < 0) {
      return -1;
    }
    return 0;
  }

  AttrType type() const override {
    return DATES;
  }

  bool is_null() const override {
    return is_null_;
  }
private:
  time_t value_;
  bool is_null_ = false;
};

class StringValue : public TupleValue {
 public:
  StringValue(const char *value, int len) : value_(value, len) {}
  StringValue(const char *value, int len, AggregationType aggregation_type, bool is_null)
      : value_(value, len), is_null_(is_null) {
    aggregation_type_ = aggregation_type;
  }
  explicit StringValue(const char *value) : value_(value) {}
  explicit StringValue(const char *value, AggregationType aggregation_type)
      : value_(value) {
    aggregation_type_ = aggregation_type;
  }

  void to_string(std::ostream &os) const override {
    switch (aggregation_type_) {
      case CountAggregate: {
        if (is_null_) {
          os << 0;
        } else {
          os << count;
        }
      } break;
      default: {
        if (is_null_) {
          os << "NULL";
        } else {
          os << value_;
        }
      }
    }
  }

  void merge(const TupleValue &other) override {
    // NULL 不计入聚合
    if (other.is_null()) {
      return;
    }
    is_null_ = false;
    const StringValue &string_other = (const StringValue &)other;
    switch (aggregation_type_) {
      case CountAggregate: {
        count++;
      } break;
      case MaxAggregate: {
        if (compare(string_other) < 0) value_ = string_other.value_;
      } break;
      case MinAggregate: {
        if (compare(string_other) > 0) value_ = string_other.value_;
      }
      default: {
      }
    }
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }

  AttrType type() const override {
    return CHARS;
  }

  bool is_null() const override {
    return is_null_;
  }
private:
  std::string value_;
  bool is_null_ = false;
};

#endif  //__OBSERVER_SQL_EXECUTOR_VALUE_H_
