#include "gtest/gtest.h"
#include "../main/QueryBudget.h"

using namespace date;
class StubBudgetRepo : public BudgetRepo {
public:
    virtual std::vector<Budget> findAll() override
    {
		return budgets;
	}
    std::vector<Budget> budgets;
};

namespace {
    TEST(QueryBudgetTest, dailyAmount) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        budgetRepo->budgets.push_back(Budget(300, year(2023) / month(9)));
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{9}, date::day{10}),
                                            date::year_month_day(date::year{2023}, date::month{9},date::day{16}));
        ASSERT_EQ(amount,7*10);

        delete budgetRepo;
        delete queryBudget;
    }

    TEST(QueryBudgetTest, calculateSameMonth) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        budgetRepo->budgets.push_back(Budget(30, year(2023) / month(9)));
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{9}, date::day{10}),
        date::year_month_day(date::year{2023}, date::month{9},date::day{16}));
        ASSERT_EQ(amount,7);

        delete budgetRepo;
        delete queryBudget;
    }

    TEST(QueryBudgetTest, startBeforeBudgetStart) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        budgetRepo->budgets.push_back(Budget(30, year(2023) / month(9)));
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{8}, date::day{10}),
                                            date::year_month_day(date::year{2023}, date::month{9},date::day{16}));
        ASSERT_EQ(amount,16);

        delete budgetRepo;
        delete queryBudget;
    }

    TEST(QueryBudgetTest, endAfterBudgetEnd) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        budgetRepo->budgets.push_back(Budget(30, year(2023) / month(9)));
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{9}, date::day{10}),
                                            date::year_month_day(date::year{2023}, date::month{10},date::day{16}));
        ASSERT_EQ(amount,21);

        delete budgetRepo;
        delete queryBudget;
    }

    TEST(QueryBudgetTest, calculateDiffMonth) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        budgetRepo->budgets.push_back(Budget(31, year(2023) / month(7)));
        budgetRepo->budgets.push_back(Budget(31, year(2023) / month(8)));
        budgetRepo->budgets.push_back(Budget(30, year(2023) / month(9)));
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{7}, date::day{10}),
        date::year_month_day(date::year{2023}, date::month{9},date::day{16}));
        ASSERT_EQ(amount,69);

        delete budgetRepo;
        delete queryBudget;
    }

    TEST(QueryBudgetTest, missingMiddleBudget) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        budgetRepo->budgets.push_back(Budget(31, year(2023) / month(7)));
        budgetRepo->budgets.push_back(Budget(30, year(2023) / month(9)));
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{7}, date::day{10}),
                                            date::year_month_day(date::year{2023}, date::month{9},date::day{16}));
        ASSERT_EQ(amount,22 + 16);

        delete budgetRepo;
        delete queryBudget;
    }

    TEST(QueryBudgetTest, calculateDiffYear) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        budgetRepo->budgets.push_back(Budget(31, year(2023) / month(12)));
        budgetRepo->budgets.push_back(Budget(31,year(2024) / month(1)));
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{12}, date::day{10}),
        date::year_month_day(date::year{2024}, date::month{1},date::day{16}));
        ASSERT_EQ(amount,38);

        delete budgetRepo;
        delete queryBudget;
    }

    
TEST(QueryBudgetTest, calculateBefore) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        budgetRepo->budgets.push_back(Budget(30, year(2023) / month(9)));
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{4}, date::day{10}),
        date::year_month_day(date::year{2023}, date::month{5},date::day{16}));
        ASSERT_EQ(amount,0);

        delete budgetRepo;
        delete queryBudget;
    }

TEST(QueryBudgetTest, calculateAfter) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        budgetRepo->budgets.push_back(Budget(30, year(2023) / month(9)));
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2025}, date::month{4}, date::day{10}),
        date::year_month_day(date::year{2025}, date::month{5},date::day{16}));
        ASSERT_EQ(amount,0);

        delete budgetRepo;
        delete queryBudget;
    }
}