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

    TEST_F(QueryBudgetTest, StartSameAsEnd) {
        givenBudget(Budget(30, year(2024)/month(9)));

        int total = target->Calculate(year(2024)/month(9)/day(20), year(2024)/month(9)/day(20));

        ASSERT_EQ(1, total);
    }



}