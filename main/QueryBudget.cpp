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
                int dayNum = (sys_days{end} - sys_days{start}).count() + 1;
                allAmount = dayNum * budget.GetDailyAmount();
            }
        }else{
        //去除首尾
            date::year_month ym_start = startYear / startMonth + months{1};
            date::year_month ym_end = endYear / endMonth - months{1};
            for (year_month ym = ym_start; ym <= ym_end; ym += months{1}) {
                if(budget.GetYearMonth() == ym){
                    allAmount += budget.GetAmount();
                }
            }
            if(budget.GetYearMonth() == year_month(startYear,startMonth)){
                int dayNum = (sys_days{start.year() / start.month() / last} - sys_days{start}).count() + 1;
                allAmount += dayNum * budget.GetDailyAmount();
            }
            if(budget.GetYearMonth() == year_month(endYear,endMonth)){
                int dayNum = (sys_days{end} - sys_days{end.year() / end.month() / 1}).count() + 1;
                allAmount += dayNum * budget.GetDailyAmount();
            }
        }
    }
    return allAmount;
}

