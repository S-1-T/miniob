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
// Created by Wangyunlai on 2022/07/08.
//

#pragma once

#include <functional>

namespace common {

class DeferHelper
{
public: 
  DeferHelper(const std::function<void()> defer) : defer_(std::move(defer))
  {}

  ~DeferHelper()
  {
    if (defer_) {
      defer_();
    }
  }

private:
  const std::function<void()> defer_;
};

} // namespace common

#define DERFER_NAME(suffix) defer_helper_##suffix
#define DEFER(callback) common::DeferHelper DERFER_NAME(__LINE__)(callback)
