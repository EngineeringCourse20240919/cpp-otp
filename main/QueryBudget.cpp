#include "QueryBudget.h"
#include <iostream>

QueryBudget::QueryBudget(BudgetRepo *budgetRepo): budgetRepo(budgetRepo) {

}

unsigned int QueryBudget::Calculate(const year_month_day& start, const year_month_day& end)
{
    std::vector<Budget> budgets = budgetRepo->findAll();
    int allAmount = 0;
    for(Budget budget:budgets){
        year startYear = start.year();
        year endYear = end.year();
        month startMonth = start.month();
        month endMonth = end.month();
        if(startYear == endYear && startMonth == endMonth){
            if(budget.GetYearMonth() == year_month(startYear,startMonth)){
                int dayNum = getOverlappingDayNum(start, end, budget);
                allAmount = dayNum * budget.GetDailyAmount();
            }
        }else{
        //去除首尾
            date::year_month ym_start = startYear / startMonth + months{1};
            date::year_month ym_end = endYear / endMonth - months{1};
            for (year_month ym = ym_start; ym <= ym_end; ym += months{1}) {
                if(budget.GetYearMonth() == ym){
                    int dayNum = getOverlappingDayNum(start, end, budget);
                    allAmount += dayNum * budget.GetDailyAmount();
                }
            }
            if(budget.GetYearMonth() == year_month(startYear,startMonth)){
                int dayNum = getOverlappingDayNum(start, end, budget);
                allAmount += dayNum * budget.GetDailyAmount();
            }
            if(budget.GetYearMonth() == year_month(endYear,endMonth)){
                int dayNum = getOverlappingDayNum(start, end, budget);
                allAmount += dayNum * budget.GetDailyAmount();
            }
        }
    }
    return allAmount;
}

int QueryBudget::getOverlappingDayNum(const year_month_day &start, const year_month_day &end, Budget& budget) const {
    year_month_day overlappingEnd = end < budget.GetYearMonth() / last ? end : budget.GetYearMonth() / last;
    year_month_day overlappingStart = start > budget.GetYearMonth() / 1 ? start : budget.GetYearMonth() / 1;
    return (sys_days{overlappingEnd} - sys_days{overlappingStart}).count() + 1;
}

