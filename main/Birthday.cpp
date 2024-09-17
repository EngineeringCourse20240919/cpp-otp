#include "Birthday.h"

Birthday::Birthday(Today *today) : today(today) {}

bool Birthday::IsBirthday() {
    return today->GetToday().month() == date::month{4} && today->GetToday().day() == date::day{9};
}
