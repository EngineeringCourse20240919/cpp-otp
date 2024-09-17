#include "gtest/gtest.h"
#include "../main/Birthday.h"

using namespace date;

class StubToday : public Today {
public:
    year_month_day GetToday() override {
        return today;
    }
    year_month_day today;
};

namespace {

    TEST(BirthdayTest, is_birthday) {
        StubToday* stubToday = new StubToday();
        stubToday->today = year(2024) / month(4) / day(9);
        Birthday birthday = Birthday(stubToday);

        ASSERT_TRUE(birthday.IsBirthday());
    }

    TEST(BirthdayTest, is_not_birthday) {
        StubToday* stubToday = new StubToday();
        stubToday->today = year(2024) / month(5) / day(9);
        Birthday birthday = Birthday(stubToday);

        ASSERT_FALSE(birthday.IsBirthday());
    }
}