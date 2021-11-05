//
// Created by 69118 on 2021/10/19.
//

#include <cstring>
#include <ctime>
#include <algorithm>

#include "common/log/log.h"
#include "storage/common/type/convert.h"
#include "storage/common/type/date.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/text.h"


static const bool type_convertable[9][9] = {
    {0, 0, 0, 0, 0, 0, 1, 0, 0},  /* UNDEFINE 与其他任何一种类型不可比较 */
    {0, 1, 0, 0, 1, 1, 1, 0, 0},  /* CHARS 可与 CHARS, DATES, TEXTS, NULL_ 比较 */
    {0, 0, 1, 1, 0, 0, 1, 0, 0},  /* INTS 可与 FLOATS 进行隐式转换 */
    {0, 0, 1, 1, 0, 0, 1, 0, 0},  /* FLOATS 可与 INTS 进行隐式转换 */
    {0, 1, 0, 0, 1, 0, 1, 0, 0},  /* DATES 目前仅可与自身和 CHARS 比较 */
    {0, 1, 0, 0, 0, 1, 1, 0, 0},  /* TEXTS 可与 CHARS, TEXTS, NULL_ 比较 */
    {1, 1, 1, 1, 1, 1, 1, 1, 1},  /* NULL 可以和任何值比较，但是返回都是 false */
    {0, 0, 0, 0, 0, 0, 1, 0, 0},  /* SELECTS */
    {0, 0, 0, 0, 0, 0, 1, 0, 0},  /* TUPLESET */
};

bool is_type_convertable(AttrType t1, AttrType t2) {
  return type_convertable[t1][t2];
}