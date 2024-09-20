#include "BudgetRepo.h"

Budget::Budget(int amount, const date::year_month &yearMonth) : amount(amount), yearMonth(yearMonth) {}

int Budget::GetAmount() {
    return amount;
}

year_month Budget::GetYearMonth() {
    return yearMonth;
}

year_month_day Budget::GetStart() {
    return yearMonth / 1;
}

year_month_day Budget::GetEnd() {
    return yearMonth / last;
}

std::vector<Budget> BudgetRepo::findAll() {
    return std::vector<Budget>();
}
