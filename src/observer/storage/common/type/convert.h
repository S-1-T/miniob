//
// Created by 69118 on 2021/10/19.
//

#ifndef MINIDB_CONVERT_H
#define MINIDB_CONVERT_H

#include "sql/parser/parse_defs.h"
#include "rc.h"

bool is_type_convertable(AttrType t1, AttrType t2);

#endif //MINIDB_CONVERT_H
