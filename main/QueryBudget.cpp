#include "QueryBudget.h"

QueryBudget::QueryBudget(BudgetRepo *budgetRepo) : budgetRepo(budgetRepo) {

}

unsigned int QueryBudget::Calculate(const year_month_day &start, const year_month_day &end) {
    if (budgetRepo->findAll().empty()) {
        return 0;
    }
    return 1;
}
