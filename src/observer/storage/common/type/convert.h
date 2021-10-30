//
// Created by 69118 on 2021/10/19.
//

#ifndef MINIDB_CONVERT_H
#define MINIDB_CONVERT_H

#include "sql/parser/parse_defs.h"
#include "rc.h"

bool is_type_convertable(AttrType t1, AttrType t2);

RC convert_type(AttrType src_type, void *src_data, AttrType dest_type, void *dest_data, int len, bool is_null);

#endif //MINIDB_CONVERT_H
