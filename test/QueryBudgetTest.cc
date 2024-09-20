#include "gtest/gtest.h"
#include "../main/QueryBudget.h"
#include "gmock/gmock.h"

class StubBudgetRepo : public BudgetRepo {
public:
    MOCK_METHOD(std::vector<Budget>, findAll, ());
};

using namespace ::testing;

namespace {

    class QueryBudgetTest : public Test {
    protected:
        StubBudgetRepo *stubBudgetRepo;
        QueryBudget* target;
        void SetUp() {
            stubBudgetRepo = new StubBudgetRepo();
            target = new QueryBudget(stubBudgetRepo);
        }
        void TearDown() {
            delete stubBudgetRepo;
            delete target;
        }
        void givenBudget(const Budget& budget) {
            std::vector<Budget> budgets = std::vector<Budget>{ budget };
            ON_CALL(*stubBudgetRepo, findAll()).WillByDefault(Return(budgets));
        }
    };

    TEST_F(QueryBudgetTest, NoBudget) {
        int total = target->Calculate(year(2024)/month(9)/day(20), year(2024)/month(9)/day(20));

        ASSERT_EQ(0, total);
    }

    TEST_F(QueryBudgetTest, StartSameAsEnd_OneBudget) {
        givenBudget(Budget(30, year(2024)/month(9)));

        int total = target->Calculate(year(2024)/month(9)/day(20), year(2024)/month(9)/day(20));

        ASSERT_EQ(1, total);
    }


    TEST_F(QueryBudgetTest, StartEndSameMonth_OneBudget) {
        givenBudget(Budget(30, year(2024)/month(9)));

        int total = target->Calculate(year(2024)/month(9)/day(20), year(2024)/month(9)/day(25));

        ASSERT_EQ(6, total);
    }

    TEST_F(QueryBudgetTest, StartBeforeBudgetStart_OneBudget) {
        givenBudget(Budget(30, year(2024)/month(9)));

        int total = target->Calculate(year(2024)/month(8)/day(20), year(2024)/month(9)/day(25));

        ASSERT_EQ(25, total);
    }

    TEST_F(QueryBudgetTest, StartAfterBudgetEnd_OneBudget) {
        givenBudget(Budget(30, year(2024)/month(9)));

        int total = target->Calculate(year(2024)/month(10)/day(20), year(2024)/month(10)/day(25));

        ASSERT_EQ(0, total);
    }

    TEST_F(QueryBudgetTest, EndBeforeBudgetStart_OneBudget) {
        givenBudget(Budget(30, year(2024)/month(9)));

        int total = target->Calculate(year(2024)/month(8)/day(20), year(2024)/month(8)/day(25));

        ASSERT_EQ(0, total);
    }

    TEST_F(QueryBudgetTest, EndAfterBudgetEnd_OneBudget) {
        givenBudget(Budget(30, year(2024)/month(9)));

        int total = target->Calculate(year(2024)/month(9)/day(20), year(2024)/month(10)/day(10));

        ASSERT_EQ(11, total);
    }

    TEST_F(QueryBudgetTest, TwoBudgets) {
        std::vector<Budget> budgets = std::vector<Budget>{ Budget(30, year(2024)/month(9)), Budget(31, year(2024)/month(10)) };
        ON_CALL(*stubBudgetRepo, findAll()).WillByDefault(Return(budgets));

        int total = target->Calculate(year(2024)/month(9)/day(20), year(2024)/month(10)/day(10));

        ASSERT_EQ(11 + 10, total);
    }


    TEST_F(QueryBudgetTest, DailyAmount) {
        givenBudget(Budget(60, year(2024)/month(9)));

        int total = target->Calculate(year(2024)/month(9)/day(20), year(2024)/month(10)/day(10));

        ASSERT_EQ(11 * 2, total);
    }

}