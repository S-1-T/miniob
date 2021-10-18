#ifndef __OBSERVER_STORAGE_COMMON_TYPE_DATE_H__
#define __OBSERVER_STORAGE_COMMON_TYPE_DATE_H__

#include <ctime>

#include "common/log/log.h"

class Date {
   public:
    Date(char *date_str);
    ~Date();

    time_t get_inner_date_time_t();

   private:
    struct tm *date_tm = nullptr;
};

#endif  // __OBSERVER_STORAGE_COMMON_TYPE_DATE_H__