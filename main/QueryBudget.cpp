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
            int amount = budget.GetAmount();
            year_month_day lastDay = start.year() / start.month() / last;
            year_month_day firstDay = start.year() / start.month() / 1;
            int eachDay = (budget.GetAmount() / ((sys_days{lastDay} - sys_days{firstDay}).count() + 1));
            allAmount = dayNum * eachDay;
            }
        }else{
        //去除首尾
            date::year startYearTemp = startYear;
            date::year endYearTemp = endYear;
            date::month startMonthTemp = startMonth;
            date::month endMonthTemp = endMonth;
            startMonthTemp++;
            endMonthTemp--;
            if(startMonthTemp == date::month{1}){
                startYearTemp++;
            }
            if(endMonthTemp == date::month{12}){
                endYearTemp--;
            }
            date::year_month ym_start = startYearTemp / date::month{startMonthTemp};
            date::year_month ym_end = endYearTemp /date::month{endMonthTemp};
            if(ym_start <= ym_end){
            for (year_month ym = ym_start; ym <= ym_end; ym += months{1}) {
                std::cout << ym << "\n";
                if(budget.GetYearMonth() == ym){
                        allAmount += budget.GetAmount();
                    }
            }
            }
            if(budget.GetYearMonth() == year_month(startYear,startMonth)){
                year_month_day firstDay = start.year() / start.month() / 1;
                year_month_day lastDay = start.year() / start.month() / last;
                int startDayNum = (sys_days{start.year() / start.month() / last} - sys_days{start}).count() + 1;
                int eachDay = (budget.GetAmount() / ((sys_days{lastDay} - sys_days{firstDay}).count() + 1));
                allAmount += startDayNum * eachDay;
            }
            if(budget.GetYearMonth() == year_month(endYear,endMonth)){
                year_month_day firstDay = end.year() / end.month() / 1;
                year_month_day lastDay = end.year() / end.month() / last;
                int endDayNum = (sys_days{end} - sys_days{end.year() / end.month() / 1}).count() + 1;
                int eachDay = (budget.GetAmount() / ((sys_days{lastDay} - sys_days{firstDay}).count() + 1));
                allAmount += endDayNum * eachDay;
            }
        }
    }
    return allAmount;
}

