#ifndef CPP_OTP_TODAY_H
#define CPP_OTP_TODAY_H
#include "date.h"


class Today {
public:
    virtual date::year_month_day GetToday();
};


#endif //CPP_OTP_TODAY_H
