/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include <string>
#include <cstring>

const char *format_double(double value) {
  int sz = std::snprintf(nullptr, 0, "%.2f", value);
  char *output = new char[sz + 1];
  memset(output, 0, sz + 1);
  std::snprintf(output, sz + 1, "%.2f", value);
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
  return output;
}