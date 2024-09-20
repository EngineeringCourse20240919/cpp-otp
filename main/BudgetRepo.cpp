#include "BudgetRepo.h"

Budget::Budget(int amount, const date::year_month &yearMonth) : amount(amount), yearMonth(yearMonth) {}

int Budget::GetAmount() {
    return amount;
}

year_month Budget::GetYearMonth() {
    return yearMonth;
}

int Budget::GetDailyAmount() const {
    year_month_day lastDay = yearMonth / last;
    return amount / (unsigned int) (lastDay.day());
}

std::vector<Budget> BudgetRepo::findAll() {
    return std::vector<Budget>();
}
