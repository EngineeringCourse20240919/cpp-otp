#include "QueryBudget.h"

QueryBudget::QueryBudget(BudgetRepo *budgetRepo) : budgetRepo(budgetRepo) {

}

unsigned int QueryBudget::Calculate(const year_month_day &start, const year_month_day &end) {
    int total = 0;

    for (Budget budget : budgetRepo->findAll()) {
        total += getOverlappingDayCount(start, end, budget);
    }

    return total;
}

unsigned int
QueryBudget::getOverlappingDayCount(const year_month_day &start, const year_month_day &end, Budget &budget) const {
    if (start > budget.GetEnd() || end < budget.GetStart()) {
        return 0;
    }
    if (end > budget.GetEnd()) {
        return (sys_days(budget.GetEnd()) - sys_days(start)).count() + 1;
    }
    if (start < budget.GetStart()) {
        return (sys_days(end) - sys_days(budget.GetStart())).count() + 1;
    }
    return (sys_days(end) - sys_days(start)).count() + 1;
}
