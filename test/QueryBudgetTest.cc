#include "gtest/gtest.h"
#include "../main/QueryBudget.h"

using namespace date;
class StubBudgetRepo : public BudgetRepo {
public:
    virtual std::vector<Budget> findAll() override
    {
        std::vector<Budget> budgets;

	    budgets.push_back(Budget(31, date::year_month(date::year{ 2023 }, date::month{ 7 })));
		budgets.push_back(Budget(31, date::year_month(date::year{ 2023 }, date::month{ 8 })));
		budgets.push_back(Budget(30, date::year_month(date::year{ 2023 }, date::month{ 9 })));
		budgets.push_back(Budget(31, date::year_month(date::year{ 2023 }, date::month{ 10 })));
		budgets.push_back(Budget(30, date::year_month(date::year{ 2023 }, date::month{ 11 })));
		budgets.push_back(Budget(31, date::year_month(date::year{ 2023 }, date::month{ 12 })));
		budgets.push_back(Budget(31, date::year_month(date::year{ 2024 }, date::month{ 1 })));
		budgets.push_back(Budget(29, date::year_month(date::year{ 2024 }, date::month{ 2 })));
		budgets.push_back(Budget(31, date::year_month(date::year{ 2024 }, date::month{ 3 })));
		budgets.push_back(Budget(30, date::year_month(date::year{ 2024 }, date::month{ 4 })));
		budgets.push_back(Budget(31, date::year_month(date::year{ 2024 }, date::month{ 5 })));
		budgets.push_back(Budget(30, date::year_month(date::year{ 2024 }, date::month{ 6 })));
		budgets.push_back(Budget(31, date::year_month(date::year{ 2024 }, date::month{ 7 })));
		budgets.push_back(Budget(31, date::year_month(date::year{ 2024 }, date::month{ 8 })));
		budgets.push_back(Budget(30, date::year_month(date::year{ 2024 }, date::month{ 9 })));
		budgets.push_back(Budget(31, date::year_month(date::year{ 2024 }, date::month{ 10 })));
		budgets.push_back(Budget(30, date::year_month(date::year{ 2024 }, date::month{ 11 })));
		budgets.push_back(Budget(31, date::year_month(date::year{ 2024 }, date::month{ 12 })));
		return budgets;
	}
};

namespace {
    TEST(QueryBudgetTest, calculateSameMonth) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{9}, date::day{10}),
        date::year_month_day(date::year{2023}, date::month{9},date::day{16}));
        ASSERT_EQ(amount,7);

        delete budgetRepo;
        delete queryBudget;
    }

TEST(QueryBudgetTest, calculateDiffMonth) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{7}, date::day{10}),
        date::year_month_day(date::year{2023}, date::month{9},date::day{16}));
        ASSERT_EQ(amount,69);

        delete budgetRepo;
        delete queryBudget;
    }

TEST(QueryBudgetTest, calculateDiffYear) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{12}, date::day{10}),
        date::year_month_day(date::year{2024}, date::month{1},date::day{16}));
        ASSERT_EQ(amount,38);

        delete budgetRepo;
        delete queryBudget;
    }

    
TEST(QueryBudgetTest, calculateBefore) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2023}, date::month{4}, date::day{10}),
        date::year_month_day(date::year{2023}, date::month{5},date::day{16}));
        ASSERT_EQ(amount,0);

        delete budgetRepo;
        delete queryBudget;
    }

TEST(QueryBudgetTest, calculateAfter) {
        StubBudgetRepo* budgetRepo = new StubBudgetRepo();
        QueryBudget *queryBudget = new QueryBudget(budgetRepo);
        int amount = queryBudget->Calculate(date::year_month_day(date::year{2025}, date::month{4}, date::day{10}),
        date::year_month_day(date::year{2025}, date::month{5},date::day{16}));
        ASSERT_EQ(amount,0);

        delete budgetRepo;
        delete queryBudget;
    }
}