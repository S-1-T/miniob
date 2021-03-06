#include "storage/common/type/date.h"

#include <regex>

static const char *exception_msg = "Unable to create a Date type.";

Date::Date(char *date_str) {
  // 初步检查日期格式是否合法：YYYY-MM-DD 或 YYYY-M-D
  // 合法日期下限：1970.1.1
  std::regex date_reg(
      "((19[7-9][0-9]|20[0-9]{2})-([1-9]|0[1-9]|1[0-2])-([1-9]|0[1-9]|[12][0-9]"
      "|3[01]))");
  if (std::regex_match(date_str, date_reg)) {
    time_t rawtime;
    time(&rawtime);
    date_tm = localtime(&rawtime);
    int pos = 0;
    int year = 0, month = 0, day = 0;
    char *pch = strtok(date_str, "-");
    while (pch != NULL) {
      if (pos == 0) {
        year = atoi(pch);
      } else if (pos == 1) {
        month = atoi(pch);
      } else if (pos == 2) {
        day = atoi(pch);
      }
      pos++;
      pch = strtok(NULL, "-");
    }
    // 进一步检查日期是否合法
    switch (month) {
      case 2: {
        if ((year % 4 != 0 && day > 28) || (year % 4 == 0 && day > 29)) {
          LOG_ERROR(
              "Unsupported date format: incorrect day with the given month.");
          throw exception_msg;
        }
        break;
      }
      case 4:
      case 6:
      case 9:
      case 11: {
        if (day > 30) {
          LOG_ERROR(
              "Unsupported date format: incorrect day with the given month.");
          throw exception_msg;
        }
        break;
      }
    }
    date_tm->tm_year = year - 1900;
    date_tm->tm_mon = month - 1;
    date_tm->tm_mday = day;
    date_tm->tm_hour = 0;
    date_tm->tm_min = 0;
    date_tm->tm_sec = 0;
  } else {
    LOG_ERROR("Unsupported date format: incorrect date format.");
    throw exception_msg;
  }
}

Date::~Date() { date_tm = nullptr; }

time_t Date::get_inner_date_time_t() { return mktime(date_tm); };