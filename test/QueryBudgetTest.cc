#include "gtest/gtest.h"
#include "../main/QueryBudget.h"

class StubBudgetRepo : public BudgetRepo {

};

namespace {

    TEST(QueryBudgetTest, NoBudget) {
        StubBudgetRepo* stubBudgetRepo = new StubBudgetRepo();
        QueryBudget target = QueryBudget(stubBudgetRepo);

        int total = target.Calculate(year(2024)/month(9)/day(20), year(2024)/month(9)/day(20));

        ASSERT_EQ(0, total);

        delete stubBudgetRepo;
    }
    


}