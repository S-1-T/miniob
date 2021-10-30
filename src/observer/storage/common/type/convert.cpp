//
// Created by 69118 on 2021/10/19.
//

#include <cstring>
#include <ctime>
#include <algorithm>

#include "common/log/log.h"
#include "storage/common/type/convert.h"
#include "storage/common/type/date.h"


static const bool type_convertable[5][5] = {
    {0, 0, 0, 0, 0}, /* UNDEFINE 与其他任何一种类型不可比较 */
    {0, 1, 0, 0, 1}, /* CHARS 目前仅可与自身和 DATES 比较 */
    {0, 0, 1, 1, 0}, /* INTS 可与 FLOATS 进行隐式转换 */
    {0, 0, 1, 1, 0}, /* FLOATS 可与 INTS 进行隐式转换 */
    {0, 1, 0, 0, 1} /* DATES 目前仅可与自身和 CHARS 比较 */
};

bool is_type_convertable(AttrType t1, AttrType t2) {
  return type_convertable[t1][t2];
}

RC convert_type(AttrType src_type, void *src_data, AttrType dest_type, void *dest_data, int len, bool is_null) {
  if (!type_convertable[src_type][dest_type]) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  // 数据部分长度为 len - 1
  // 剩下 1 字节表示是否为 NULL
  len = len - 1;
  if (is_null) {
    memset(dest_data, 0, len);
    *((char *)dest_data + len) = (char)true;
    return RC::SUCCESS;
  }
  switch (dest_type) {
    // INTS FLOATS 考虑隐式转换
    case INTS: {
      if (src_type == FLOATS) {
        float origin = *(float *) src_data;
        int convert = (int) origin;
        memcpy(dest_data, &convert, len);
      } else {
        memcpy(dest_data, src_data, len);
      }
      break;
    }
    case FLOATS: {
      if (src_type == INTS) {
        int origin = *(int *) src_data;
        float convert = (float) origin;
        memcpy(dest_data, &convert, len);
      } else {
        memcpy(dest_data, src_data, len);
      }
      break;
    }
    case CHARS: {
      memcpy(dest_data, src_data, std::min(len, (int)strlen(static_cast<char *>(src_data)) + 1));
      break;
    }
    case DATES: {
      try {
        Date date = Date(static_cast<char *>(src_data));
        time_t date_time_t = date.get_inner_date_time_t();
        memcpy(dest_data, &date_time_t, len);
      } catch (const char *e) {
        LOG_ERROR("Invalid value data to create a Date type. e=%s",
                  e);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      break;
    }
    default:
      memcpy(dest_data, src_data, len);
  }
  // 最后一个字节表示是否是 null
  *((char *)dest_data + len) = (char)false;
  return RC::SUCCESS;
}