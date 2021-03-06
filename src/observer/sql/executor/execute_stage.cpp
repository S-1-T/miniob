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

#include <string>
#include <sstream>
#include <vector>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "storage/common/type/convert.h"

using namespace common;

RC do_cartesian(std::vector<TupleSet> &tuple_sets, const int condition_num, Condition *conditions, TupleSet &output);

RC cartesian(std::vector<TupleSet> &tuple_sets, int condition_num, Condition *conditions, std::shared_ptr<TupleValue> *values, int value_num, TupleSet &output, int index);

static RC schema_add_field(Table *table, const char *field_name, AggregationType aggregation_type, TupleSchema &schema);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new(std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new(std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  char response[256] = "";
  switch (sql->flag) {
    case SCF_SELECT: {  // select
      RC rc =
          do_select(current_db, sql, exe_event->sql_event()->session_event());
      // ??????????????? FAILURE
      if (rc != RC::SUCCESS) snprintf(response, sizeof(response), "FAILURE\n");
    }
      break;

    case SCF_INSERT:
    case SCF_UPDATE:
    case SCF_DELETE:
    case SCF_CREATE_TABLE:
    case SCF_SHOW_TABLES:
    case SCF_DESC_TABLE:
    case SCF_DROP_TABLE:
    case SCF_CREATE_INDEX:
    case SCF_DROP_INDEX:
    case SCF_LOAD_DATA: {
      StorageEvent *storage_event = new(std::nothrow) StorageEvent(exe_event);
      if (storage_event == nullptr) {
        LOG_ERROR("Failed to new StorageEvent");
        event->done_immediate();
        return;
      }

      default_storage_stage_->handle_event(storage_event);
    }
      break;
    case SCF_SYNC: {
      RC rc = DefaultHandler::get_default().sync();
      snprintf(response, sizeof(response), "%s\n", strrc(rc));
    }
      break;
    case SCF_BEGIN: {
      session_event->get_client()->session->set_trx_multi_operation_mode(true);
      snprintf(response, sizeof(response), "%s\n", strrc(RC::SUCCESS));
    }
      break;
    case SCF_COMMIT: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->commit();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      snprintf(response, sizeof(response), "%s\n", strrc(rc));
    }
      break;
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      snprintf(response, sizeof(response), "%s\n", strrc(rc));
    }
      break;
    case SCF_HELP: {
      snprintf(response, sizeof(response),
               "show tables;\n"
               "desc `table name`;\n"
               "create table `table name` (`column name` `column type`, ...);\n"
               "drop table `table name`;\n"
               "create index `index name` on `table` (`column`);\n"
               "drop index `index name` on 'table';\n"
               "insert into `table` values(`value1`,`value2`);\n"
               "update `table` set column=value [where `column`=`value`];\n"
               "delete from `table` [where `column`=`value`];\n"
               "select [ * | `columns` ] from `table`;\n");
    }
      break;
    case SCF_EXIT: {
      // do nothing
      snprintf(response, sizeof(response), "Unsupported\n");
    }
      break;
    default: {
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
  }
  if (strlen(response) > 0) session_event->set_response(response);
  exe_event->done_immediate();
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

// ?????????????????????????????????????????? index
RC check_ambiguous(size_t relation_num, Table **tables, const char *attribute_name, size_t &idx) {
  bool find = false;
  for (size_t j = 0; j < relation_num; j++) {
    auto f = tables[j]->table_meta().field(attribute_name);
    if (f != nullptr) {
      if (!find) {
        find = true;
        idx = j;
      } else {
        LOG_WARN("Column [%s] in field list is ambiguous", attribute_name);
        return RC::SCHEMA_FIELD_EXIST;
      }
    }
  }
  // ?????????????????????
  if (!find) {
    LOG_WARN("No table has field [%s]", attribute_name);
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }
  return RC::SUCCESS;
}

RC selects_attr_meta_check(const Selects &selects, Table *tables[], TupleSchema &output_schema) {
  // ?????? attr ?????? table ??????????????????????????? tables ???
  // ?????? attr ?????????????????? table ??? fields ???
  // ???????????????????????? output_schema
  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    if (attr.relation_name != nullptr) {
      Table *t = nullptr;
      for (size_t j = 0; j < selects.relation_num; j++) {
        if (0 == strcmp(attr.relation_name, selects.relations[j])) {
          t = tables[j];
          break;
        }
      }
      if (t == nullptr) {
        LOG_WARN("Table [%s] is not in selection's relations", attr.relation_name);
        return RC::MISMATCH;
      }
      if (0 == strcmp("*", attr.attribute_name)) {
        TupleSchema temp;
        TupleSchema::from_table(t, temp);
        output_schema.append(temp);
      } else if (nullptr == t->table_meta().field(attr.attribute_name)) {
        LOG_WARN("No such field [%s] in table [%s]", attr.attribute_name, attr.relation_name);
        return RC::SCHEMA_FIELD_NOT_EXIST;
      } else {
        schema_add_field(t, attr.attribute_name, attr.aggregation_type, output_schema);
      }
    } else if (attr.aggregation_type == None && 0 == strcmp("*", attr.attribute_name)) {
      for (int j = selects.relation_num - 1; j >= 0; j--) {
        TupleSchema temp;
        TupleSchema::from_table(tables[j], temp);
        output_schema.append(temp);
      }
    } else if (attr.is_num == 0 && 0 != strcmp("*", attr.attribute_name)) {
      // ???????????????
      size_t idx = 0;
      RC rc = check_ambiguous(selects.relation_num, tables, attr.attribute_name, idx);
      if (RC::SUCCESS != rc) {
        return rc;
      }
      schema_add_field(tables[idx], attr.attribute_name, attr.aggregation_type, output_schema);
    } else if (attr.aggregation_type != None && (attr.is_num == 1 || 0 == strcmp("*", attr.attribute_name))) {
      // count(1) count(*)
      // ?????????????????????????????????
      auto field = tables[0]->table_meta().field(0);
      output_schema.add(field->type(), tables[0]->name(), attr.attribute_name, attr.aggregation_type);
    }
    /* ????????? group by?????????????????????????????? group by ??? */
    if (attr.aggregation_type == AggregationType::None) {
      bool exist = false;
      for (size_t j = 0; j < selects.group_by_num; j++) {
        const RelAttr &group_by_attr = selects.group_bys[j];
        if (0 == strcmp(attr.attribute_name, group_by_attr.attribute_name)) {
          exist = true;
          break;
        }
      }
      if (selects.group_by_num > 0 && !exist) {
        LOG_WARN("select attr %s is not in group bys", attr.attribute_name);
        return RC::MISMATCH;
      }
    }
  }
  return RC::SUCCESS;
}

// ???????????? meta ??????, ??????????????? tables
// ??????????????????????????? schema
RC ExecuteStage::selects_meta_check(const char *db, const Selects &selects, Table **tables, TupleSchema &output_schema) {
  // ???????????? table
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    Table * table = DefaultHandler::get_default().find_table(db, table_name);
    if (nullptr == table) {
      LOG_WARN("No such table [%s] in db [%s]", table_name, db);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    tables[i] = table;
  }

  // ?????? group by ????????????????????????
  for (size_t i = 0; i < selects.group_by_num; i++) {
    const RelAttr &group_by_attr = selects.group_bys[i];
    if (group_by_attr.relation_name != nullptr) {
      Table *t = nullptr;
      for (size_t j = 0; j < selects.relation_num; j++) {
        if (0 == strcmp(group_by_attr.relation_name, selects.relations[j])) {
          t = tables[j];
          break;
        }
      }
      if (t == nullptr) {
        LOG_WARN("Table [%s] is not in group bys' relations", group_by_attr.relation_name);
        return RC::MISMATCH;
      }
      if (nullptr == t->table_meta().field(group_by_attr.attribute_name)) {
        LOG_WARN("No such field [%s] in table [%s]", group_by_attr.attribute_name, group_by_attr.relation_name);
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }
    } else if (group_by_attr.is_num == 0 && 0 != strcmp("*", group_by_attr.attribute_name)) {
      // ???????????????
      size_t idx = 0;
      RC rc = check_ambiguous(selects.relation_num, tables, group_by_attr.attribute_name, idx);
      if (RC::SUCCESS != rc) {
        return rc;
      }
    } else {
      LOG_WARN("Group by field [%s] invalid", group_by_attr.attribute_name);
      return RC::MISMATCH;
    }
  }

  RC rc = selects_attr_meta_check(selects, tables, output_schema);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // ?????? condition ?????? attr ??????????????????????????? tables ???
  // ????????? attr ?????????????????? table ??? fields ???
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    const char *left_table_name = condition.left_attr.relation_name;
    const char *right_table_name = condition.right_attr.relation_name;
    const char *left_attr_name = condition.left_attr.attribute_name;
    const char *right_attr_name = condition.right_attr.attribute_name;
    int left_is_attr = condition.left_is_attr;
    int right_is_attr = condition.right_is_attr;
    bool left_find = false;
    bool right_find = false;
    size_t left_table_idx = 0;
    size_t right_table_idx = 0;
    for (size_t j = 0; j < selects.relation_num; j++) {
      if (1 == left_is_attr) {
        if (left_table_name != nullptr && 0 == strcmp(left_table_name, selects.relations[j])) {
          left_find = true;
          left_table_idx = j;
        } else if (left_table_name == nullptr) {
          size_t idx = 0;
          RC rc = check_ambiguous(selects.relation_num, tables, left_attr_name, idx);
          if (RC::SUCCESS != rc) {
            return rc;
          }
        }
      }
      if (1 == right_is_attr) {
        if (right_table_name != nullptr && 0 == strcmp(right_table_name, selects.relations[j])) {
          right_find = true;
          right_table_idx = j;
        } else if (right_table_name == nullptr) {
          size_t idx = 0;
          RC rc = check_ambiguous(selects.relation_num, tables, right_attr_name, idx);
          if (RC::SUCCESS != rc) {
            return rc;
          }
        }
      }
    }
    if (1 == left_is_attr && left_table_name != nullptr && !left_find) {
      LOG_WARN("left attr's relation [%s] will not be scanned", left_table_name);
      return RC::MISMATCH;
    }
    if (1 == right_is_attr && right_table_name != nullptr && !right_find) {
      LOG_WARN("right attr's relation [%s] will not be scanned", right_table_name);
      return RC::MISMATCH;
    }
    if (left_is_attr && left_table_name != nullptr &&
        nullptr == tables[left_table_idx]->table_meta().field(left_attr_name)) {
      LOG_WARN("left attr [%s] is not exist in [%s]", left_attr_name, left_table_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    if (right_is_attr && right_table_name != nullptr &&
        nullptr == tables[right_table_idx]->table_meta().field(right_attr_name)) {
      LOG_WARN("right attr [%s] is not exist in [%s]", right_attr_name, right_table_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }
  for (size_t i = 0; i < selects.order_by_num; i++) {
    const OrderBy &order_by = selects.order_bys[i];
    const RelAttr &attr = order_by.attr;
    if (attr.relation_name != nullptr) {
      Table *t = nullptr;
      for (size_t j = 0; j < selects.relation_num; j++) {
        if (0 == strcmp(attr.relation_name, selects.relations[j])) {
          t = tables[j];
          break;
        }
      }
      if (t == nullptr) {
        // ????????????
        LOG_WARN("Table [%s] is not in selection's relations", attr.relation_name);
        return RC::MISMATCH;
      }
      if (nullptr == t->table_meta().field(attr.attribute_name)) {
        // ???????????????
        LOG_WARN("No such field [%s] in table [%s]", attr.attribute_name, attr.relation_name);
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }
    } else {
      // ???????????????
      size_t idx = 0;
      RC rc = check_ambiguous(selects.relation_num, tables, attr.attribute_name, idx);
      if (RC::SUCCESS != rc) {
        return rc;
      }
    }
  }

  return RC::SUCCESS;
}

void do_group_by(const TupleSet &before, TupleSet &after, const TupleSchema group_by_schema) {
  const TupleSchema &schema = before.schema();
  // ??? output_schema ???????????? group by ?????????
  const auto &output_schema = after.schema();
  const auto &output_fields = output_schema.fields();
  int output_size = output_fields.size();
  for (auto &before_tuple : before.tuples()) {
    Tuple after_tuple;
    for (int i = 0; i < output_size; i++) {
      const auto &field = output_fields[i];
      AggregationType agg_type = field.aggregation_type();
      int val_idx = schema.index_of_field(field.table_name(), field.field_name(), None);
      TupleValue *t = before_tuple.get(val_idx).clone();
      t->set_aggregation_type(field.aggregation_type());
      after_tuple.add(t);
    }
    int group_index = -1;
    for (int i = 0; i < after.size(); i++) {
      bool equal = true;
      const auto &group_by_fields = group_by_schema.fields();
      for (const auto& field : group_by_fields) {
        int field_index = -1;

        for (int j = output_size - 1; j >= 0; j--) {
          if (0 == strcmp(field.table_name(), output_schema.fields().at(j).table_name()) &&
              0 == strcmp(field.field_name(), output_schema.fields().at(j).field_name())) {
            field_index = j;
            break;
          }
        }

        const auto& m = after.get(i).get(field_index);
        const auto& n = after_tuple.get(field_index);

        if (m.compare_with_op(n, NOT_EQUAL)) {
          equal = false;
          break;
        }
      }

      if (equal) {
        group_index = i;
        break;
      }
    }
    after.merge(std::move(after_tuple), group_index);
  }
}

// ?????????????????????????????????????????????????????????????????????????????????where?????????????????????????????????????????????????????????
// ???????????????????????????. ???????????????????????????resolve????????????execution????????????????????????
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  Selects &selects = sql->sstr.selection;
  Table *tables[selects.relation_num];
  TupleSchema output_schema; // ????????????????????? schema, ?????????????????????
  rc = selects_meta_check(db, selects, tables, output_schema);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Selection meta test failed");
    return rc;
  }
  if (selects.group_by_num > 0) {
    output_schema.clear();
    for (size_t i = 0; i < selects.relation_num; i++) {
      TupleSchema::from_table(tables[i], output_schema);
    }
  } 
  // ??????????????????????????????????????????condition?????????????????????????????????select ????????????
  std::vector<SelectExeNode *> select_nodes;
  for (size_t i = 0; i < selects.relation_num; i++) {
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, db, session_event, selects, tables[i], *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *&tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    }
    select_nodes.push_back(select_node);
  }
  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node: select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *&tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  TupleSchema group_by_schema;
  for (int i = selects.group_by_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.group_bys[i];
    if (selects.relation_num > 1) {
      group_by_schema.add(UNDEFINED, attr.relation_name, attr.attribute_name, None);
    } else {
      group_by_schema.add(UNDEFINED, selects.relations[0], attr.attribute_name, None);
    }
  }

  std::stringstream ss;
  if (tuple_sets.size() > 1) {
    // ????????????????????????????????????join??????
    // ?????????????????? attr ?????????????????? condition
    int remain_condition_num = 0;
    Condition remain_conditions[MAX_NUM];
    for (int i = 0; i < selects.condition_num; i++) {
      const Condition &condition = selects.conditions[i];
      if (condition.left_is_attr && condition.right_is_attr &&
          condition.left_attr.relation_name != condition.right_attr.relation_name) {
        remain_conditions[remain_condition_num++] = condition;
      }
    }
    // ?????????????????????????????? tuple set ??????????????????
    TupleSet output(output_schema);
    auto rc = do_cartesian(tuple_sets, remain_condition_num, remain_conditions, output);
    if (rc != RC::SUCCESS && rc != RC::MISMATCH) {
      return rc;
    }
    if (selects.order_by_num > 0) {
      // ????????????
      output.sort(selects.order_bys, selects.order_by_num);
    }
    output.set_schema(output_schema);
    if (selects.group_by_num > 0) {
      output_schema.clear();
      selects_attr_meta_check(selects, tables, output_schema);
      TupleSchema temp(output_schema);
      temp.append(group_by_schema);
      TupleSet ouput_after_group(temp);
      do_group_by(output, ouput_after_group, group_by_schema);
      ouput_after_group.set_schema(output_schema);
      ouput_after_group.print(ss, true);
    } else {
      output.print(ss, true);
    }
  } else {
    TupleSet &output = tuple_sets.front();
    if (selects.order_by_num > 0) {
      // ????????????
      output.sort(selects.order_bys, selects.order_by_num);
    }
    output.set_schema(output_schema);
    if (selects.group_by_num > 0) {
      output_schema.clear();
      selects_attr_meta_check(selects, tables, output_schema);
      TupleSchema temp(output_schema);
      temp.append(group_by_schema);
      TupleSet ouput_after_group(temp);
      do_group_by(output, ouput_after_group, group_by_schema);
      ouput_after_group.set_schema(output_schema);
      ouput_after_group.print(ss, false);
    } else {
      // ???????????????????????????????????????????????????
      output.print(ss, false);
    }
  }

  for (SelectExeNode *&tmp_node: select_nodes) {
    delete tmp_node;
  }

  for (size_t i = 0; i < selects.condition_num; i++) {
    if (selects.conditions[i].left_is_attr == 2 ) {
      delete (TupleSet*)selects.conditions[i].left_value.data;
    }
    if (selects.conditions[i].right_is_attr == 2 ) {
      delete (TupleSet*)selects.conditions[i].right_value.data;
    }
  }

  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}

RC ExecuteStage::do_subSelect(const char *db, Selects &selects, SessionEvent *session_event, TupleSet &tupleSet) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  Table *tables[selects.relation_num];
  TupleSchema output_schema; // ????????????????????? schema, ?????????????????????
  rc = selects_meta_check(db, selects, tables, output_schema);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Selection meta test failed");
    return rc;
  }

  // ??????????????????????????????????????????condition?????????????????????????????????select ????????????
  std::vector<SelectExeNode *> select_nodes;
  for (size_t i = 0; i < selects.relation_num; i++) {
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, db, session_event, selects, tables[i], *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *&tmp_node: select_nodes) {
        delete tmp_node;
      }
      return rc;
    }
    select_nodes.push_back(select_node);
  }
  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node: select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *&tmp_node: select_nodes) {
        delete tmp_node;
      }
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  if (tuple_sets.size() > 1) {
    // ????????????????????????????????????join??????
    // ?????????????????? attr ?????????????????? condition
    int remain_condition_num = 0;
    Condition remain_conditions[MAX_NUM];
    for (int i = 0; i < selects.condition_num; i++) {
      const Condition &condition = selects.conditions[i];
      if (condition.left_is_attr && condition.right_is_attr &&
          condition.left_attr.relation_name != condition.right_attr.relation_name) {
        remain_conditions[remain_condition_num++] = condition;
      }
    }
    // ?????????????????????????????? tuple set ??????????????????
    TupleSet output(output_schema);
    auto rc = do_cartesian(tuple_sets, remain_condition_num, remain_conditions, output);
    if (rc != RC::SUCCESS && rc != RC::MISMATCH) {
      return rc;
    }
    output.set_schema(output_schema);
    tupleSet = std::move(output);
  } else {
    // ???????????????????????????????????????????????????
    tupleSet = std::move(tuple_sets.front());
  }

  for (SelectExeNode *&tmp_node: select_nodes) {
    delete tmp_node;
  }

  for (size_t i = 0; i<selects.condition_num; i++) {
    if (selects.conditions[i].left_is_attr == 2) {
      delete (TupleSet*)selects.conditions[i].left_value.data;
    }
    if (selects.conditions[i].right_is_attr == 2) {
      delete (TupleSet*)selects.conditions[i].right_value.data;
    }
  }

  return rc;
}

// do_cartesian ??????????????????????????????????????? TupleSet???
// ???????????? selects ???????????????????????? condition ???????????????
// ???????????????????????? condition?????????????????? scan ???????????????
RC do_cartesian(std::vector<TupleSet> &tuple_sets, const int condition_num, Condition *conditions, TupleSet &output) {
  RC rc = RC::SUCCESS;
  TupleSchema new_schema;
  TupleSchema output_schema = output.schema();
  // ???????????? tuple set ?????????
  int table_num = tuple_sets.size();
  for (int i = table_num - 1; i >= 0; i--) {
    TupleSet &tuple_set = tuple_sets[i];
    new_schema.append(tuple_set.get_schema());
  }
  // ????????????
  new_schema.append(output_schema);
  output = TupleSet(new_schema);

  auto *values = new std::shared_ptr<TupleValue>[new_schema.fields().size()];

  rc = cartesian(tuple_sets, condition_num, conditions, values, 0, output, table_num - 1);
  delete[] values;
  return rc;
}

// ?????? 6 ????????????
// ???????????????????????? value_num ???????????????????????? value_num ????????????????????????
RC cartesian(std::vector<TupleSet> &tuple_sets, int condition_num, Condition *conditions,
             std::shared_ptr<TupleValue> *values, int value_num, TupleSet &output, int index) {
  /*
   * schema ??????????????? tuple_sets ??? schema ??????????????? + ?????????????????? schema
   * ?????????
   * ?????? tuple_sets ??? schema ??? [[t1.a, t1.b], [t2.a, t2.b]]???
   * output_schema ??? [t2.b, t1.a]???
   * ????????? schema ???????????? [t2.a, t2.b, t1.a, t1.b, t2.b, t1.a]???
   * ?????? values ???????????????????????? ???[t2.a, t2.b, t1.a, t1.b]??? ?????????
   * ??????????????? tuple ??????????????????????????? ???[t2.b, t1.a]?????????????????????[t2.a, t2.b, t1.a, t1.b]???????????? value???
   * ???????????????????????????????????????????????? tuple ??? values??????????????? tuple ?????? TupleSet output ??????
   * ??? TupleSet ???????????????????????? schema ????????????????????????
   * ???????????? Projection ?????????
   */
  auto &schema = output.schema();
  const TupleSet &current_set = tuple_sets[index];
  if (value_num > 0) {
    // ?????????????????????????????????????????????, ?????? condition?????????????????????
    for (int i = 0; i < condition_num; i++) {
      Condition &condition = conditions[i];
      int left_idx = schema.index_of_field(
        condition.left_attr.relation_name, 
        condition.left_attr.attribute_name,
        condition.left_attr.aggregation_type
      );
      int right_idx = schema.index_of_field(
        condition.right_attr.relation_name, 
        condition.right_attr.attribute_name,
        condition.right_attr.aggregation_type
      );
      if (left_idx >= value_num || right_idx >= value_num) {
        continue;
      }
      const TupleValue *left = values[left_idx].get();
      const TupleValue *right = values[right_idx].get();
      if (!is_type_convertable(left->type(), right->type())) {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      if (!left->compare_with_op(*right, condition.comp)) {
        return RC::MISMATCH;
      }
    }
  }
  if (index == -1) {
    Tuple output_tuple;
    // ????????????????????? output ??? schema ??????????????????????????????????????????
    int output_num = schema.fields().size() - value_num;
    std::shared_ptr<TupleValue> output_value[output_num];
    for (int i = 0; i < output_num; i++) {
      auto field = schema.field(value_num + i);
      int val_idx = schema.index_of_field(field.table_name(), field.field_name(), field.aggregation_type());
      output_value[i] = values[val_idx];
    }
    for (int i = 0; i < output_num; i++) {
      // ???????????? select ?????????
      output_tuple.add(output_value[i]);
    }
  
    output.merge(std::move(output_tuple));

    return RC::SUCCESS;
  }
  for (int i = 0; i < current_set.size(); i++) {
    auto & current_tuple = current_set.get(i);
    int current_tuple_size = current_tuple.size();
    for (int j = 0; j < current_tuple_size; j++) {
      values[value_num + j] = current_tuple.get_pointer(j);
    }
    value_num += current_tuple_size;
    auto rc = cartesian(tuple_sets, condition_num, conditions, values, value_num, output, index - 1);
    if (rc != RC::SUCCESS && rc != RC::MISMATCH) {
      return rc;
    }
    value_num -= current_tuple_size;
  }
  return RC::SUCCESS;
}

bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}

static RC schema_add_field(Table *table, const char *field_name, AggregationType aggregation_type, TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }
  if (aggregation_type == None)
    schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
  else
    schema.add(field_meta->type(), table->name(), field_meta->name(), aggregation_type);
  return RC::SUCCESS;
}

// ??????????????????????????????????????????condition?????????????????????????????????select ????????????
RC ExecuteStage::create_selection_executor(Trx *trx, const char *db, SessionEvent *session_event,
                                           Selects &selects, Table *table, SelectExeNode &select_node) {
  // ???????????????????????????Attr
  TupleSchema schema;

  const char *table_name = table->name();

  bool has_aggregation = false;
  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    if (attr.aggregation_type != None)
      has_aggregation = true;
  }
  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
      if (0 == strcmp("*", attr.attribute_name)) {
        if (attr.aggregation_type != None) {
          // count(*)
          if (attr.aggregation_type != CountAggregate) {
            return RC::MISMATCH;
          }
          schema.add(INTS, table->name(), attr.attribute_name, attr.aggregation_type);
          continue;
        } else {
          // ???????????????????????????
          TupleSchema::from_table(table, schema);
        }
        break; // ?????????????????????* ??????????????????????????????
      } else if (attr.aggregation_type != None && attr.is_num) {
        // count(1)
        if (attr.aggregation_type != CountAggregate) {
          return RC::MISMATCH;
        }
        schema.add(INTS, table->name(), attr.attribute_name, attr.aggregation_type);
      } else {
        // ???????????????????????????
        RC rc = schema_add_field(table, attr.attribute_name, attr.aggregation_type, schema);
        if (match_table(selects, attr.relation_name, table_name) && rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }
  

  // ???????????????????????????????????????, ??????????????????????????????
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // ???????????????
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // ???????????????????????????
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // ?????????????????????????????????
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
         match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)) // ?????????????????????????????????????????????
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    } else if (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
               condition.left_attr.relation_name != nullptr && condition.left_attr.relation_name != condition.right_attr.relation_name) {
      // ????????????????????????
      schema_add_field(table, condition.left_attr.attribute_name, condition.left_attr.aggregation_type, schema);
      schema_add_field(table, condition.right_attr.attribute_name, condition.right_attr.aggregation_type, schema);
    } else if (condition.left_is_attr == 2 || condition.right_is_attr == 2) {
      TupleSet* tupleSet = new TupleSet;
      Selects sub_select;
      Value* value = nullptr;

      if (condition.left_is_attr == 2) {
        sub_select = *reinterpret_cast<Selects*>(condition.left_value.data);
        value = &const_cast<Condition&>(condition).left_value;
      } else {
        sub_select = *reinterpret_cast<Selects*>(condition.right_value.data);
        value = &const_cast<Condition&>(condition).right_value;
      }

      RC rc = do_subSelect(db, sub_select, session_event, *tupleSet);
      if (rc != RC::SUCCESS) {
        delete tupleSet;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        value_destroy(value);
        return rc;
      }
      if (tupleSet->schema().fields().size() != 1) {
        LOG_WARN("tuple set column size is not 1, cannot be compare");
        value_destroy(value);
        return RC::MISMATCH;
      }
      value_destroy(value);

      value->type = TUPLESET;
      value->data = malloc(sizeof(TupleSet*));
      value->data = tupleSet;

      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }

      condition_filters.push_back(condition_filter);
    }
  }
  // ?????? ORDER BY ???????????????
  for (int i = selects.order_by_num - 1; i >= 0; i--) {
    OrderBy &order_by = selects.order_bys[i];
    RelAttr &attr = order_by.attr;
    if (attr.relation_name == nullptr) {
      attr.relation_name = strdup(table->name());
    }
    schema_add_field(table, attr.attribute_name, AggregationType::None, schema);
  }
  if (selects.group_by_num > 0) {
    schema.clear();
    // ????????? group by ???????????????
    TupleSchema::from_table(table, schema);
  } 
  return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
}
