#include "QueryBudget.h"
#include <iostream>

QueryBudget::QueryBudget(BudgetRepo *budgetRepo): budgetRepo(budgetRepo) {

}

unsigned int QueryBudget::Calculate(const year_month_day& start, const year_month_day& end)
{
    int allAmount = 0;
    for(Budget budget: budgetRepo->findAll()) {
        allAmount += budget.GetOverlappingAmount(start, end);
    }
    return allAmount;
}

