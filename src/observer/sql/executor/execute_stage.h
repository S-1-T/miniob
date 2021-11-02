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
// Created by Longda on 2021/4/13.
//

#ifndef __OBSERVER_SQL_EXECUTE_STAGE_H__
#define __OBSERVER_SQL_EXECUTE_STAGE_H__

#include "storage/common/table.h"
#include "common/seda/stage.h"
#include "sql/parser/parse.h"
#include "sql/executor/tuple.h"
#include "rc.h"
#include "execution_node.h"

class SessionEvent;

class ExecuteStage : public common::Stage {
public:
  ~ExecuteStage();
  static Stage *make_stage(const std::string &tag);

protected:
  // common function
  ExecuteStage(const char *tag);
  bool set_properties() override;

  bool initialize() override;
  void cleanup() override;
  void handle_event(common::StageEvent *event) override;
  void callback_event(common::StageEvent *event,
                     common::CallbackContext *context) override;

  void handle_request(common::StageEvent *event);
  RC selects_meta_check(const char *db, const Selects &selects, Table **tables, TupleSchema &output_schema);
  RC do_select(const char *db, Query *sql, SessionEvent *session_event);
  RC do_subSelect(const char *db, Selects &selects, SessionEvent *session_event, TupleSet &tupleSet);
  RC create_selection_executor(Trx *trx, const char *db, SessionEvent *session_event, Selects &selects, Table *table,
  SelectExeNode &select_node);
protected:
private:
  Stage *default_storage_stage_ = nullptr;
  Stage *mem_storage_stage_ = nullptr;
};

#endif //__OBSERVER_SQL_EXECUTE_STAGE_H__
