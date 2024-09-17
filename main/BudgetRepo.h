#ifndef CPP_OTP_BUDGETREPO_H
#define CPP_OTP_BUDGETREPO_H

#include "vector"
#include "date.h"

using namespace date;

class Budget {
public:
    Budget(int amount, const year_month& yearMonth);
    int GetAmount();
    year_month GetYearMonth();

private:
    int amount;
    year_month yearMonth;
};

class BudgetRepo {
public:
    virtual std::vector<Budget> findAll();
};


#endif //CPP_OTP_BUDGETREPO_H
