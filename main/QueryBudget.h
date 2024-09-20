#ifndef CPP_OTP_QUERYBUDGET_H
#define CPP_OTP_QUERYBUDGET_H

#include "BudgetRepo.h"

class QueryBudget {
public:
    explicit QueryBudget(BudgetRepo* budgetRepo);
    unsigned int Calculate(const year_month_day& start, const year_month_day& end);
private:
    BudgetRepo* budgetRepo;
    unsigned int getOverlappingDayCount(const year_month_day &start, const year_month_day &end, Budget &budget) const;
};


#endif //CPP_OTP_QUERYBUDGET_H
