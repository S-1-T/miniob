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

#include <string.h>

#include <string>
#include <ostream>
#include <ctime>
#include <cstdio>

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream &os) const = 0;
  virtual int compare(const TupleValue &other) const = 0;
  virtual bool compare_with_op(const TupleValue &other, CompOp comp) const {
    auto cmp_result = compare(other);
    switch (comp) {
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
    return cmp_result;
  }
  virtual AttrType type() const = 0;
private:
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const IntValue & int_other = (const IntValue &)other;
    return value_ - int_other.value_;
  }

  AttrType type() const override {
    return INTS;
  }

private:
  int value_;
};

class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    int sz = std::snprintf(nullptr, 0, "%.2f", value_);
    char output[sz + 1];
    memset(output, 0, sz + 1);
    std::snprintf(output, sz + 1, "%.2f", value_);
    // 消除后缀 0
    for (int i = sz; i >= 0; i--) {
      if (output[i] != '\0' && output[i] != '0') {
        output[i + 1] = '\0';
        if (output[i] == '.') {
          output[i] = '\0';
        }
        break;
      }
    }
    os << output;
  }

  int compare(const TupleValue &other) const override {
    const FloatValue & float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (result > 0) { // 浮点数没有考虑精度问题
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
private:
  float value_;
};

class DateValue : public TupleValue {
public:
  explicit DateValue(time_t value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    struct tm *ptm = std::localtime(&value_);
    char buffer[32];
    strftime(buffer, 32, "%Y-%m-%d", ptm);
    os << buffer;
  }

  int compare(const TupleValue &other) const override {
    const DateValue & date_other = (const DateValue &)other;
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
private:
  time_t value_;
};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len) : value_(value, len){
  }
  explicit StringValue(const char *value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }

  AttrType type() const override {
    return CHARS;
  }
private:
  std::string value_;
};


#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
