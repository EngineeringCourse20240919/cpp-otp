#ifndef CPP_OTP_BUDGETREPO_H
#define CPP_OTP_BUDGETREPO_H

#include "vector"
#include "date.h"

using namespace date;

class Budget {
public:
    Budget(int amount, const year_month& yearMonth);
    int GetOverlappingAmount(const year_month_day &start, const year_month_day &end) const;

private:
    int amount;
    year_month yearMonth;
    int getOverlappingDayNum(const year_month_day &start, const year_month_day &end) const;
    int GetDailyAmount() const;
    year_month_day GetStart() const;
    year_month_day GetEnd() const;
};

class BudgetRepo {
public:
    virtual std::vector<Budget> findAll();
};


#endif //CPP_OTP_BUDGETREPO_H
