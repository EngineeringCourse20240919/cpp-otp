#include "BudgetRepo.h"

Budget::Budget(int amount, const date::year_month &yearMonth) : amount(amount), yearMonth(yearMonth) {}

int Budget::GetDailyAmount() const {
    year_month_day lastDay = yearMonth / last;
    return amount / (unsigned int) (lastDay.day());
}

year_month_day Budget::GetStart() const {
    return yearMonth / 1;
}

year_month_day Budget::GetEnd() const {
    return yearMonth / last;
}

int Budget::GetOverlappingAmount(const year_month_day &start, const year_month_day &end) const {
    return getOverlappingDayNum(start, end) * GetDailyAmount();
}

int Budget::getOverlappingDayNum(const year_month_day &start, const year_month_day &end) const {
    year_month_day overlappingEnd = end < GetEnd() ? end : GetEnd();
    year_month_day overlappingStart = start > GetStart() ? start : GetStart();
    if (overlappingStart > overlappingEnd) {
        return 0;
    }
    return (sys_days{overlappingEnd} - sys_days{overlappingStart}).count() + 1;
}

std::vector<Budget> BudgetRepo::findAll() {
    return std::vector<Budget>();
}
