#include "displayMonthly.h"

DisplayMonthly::DisplayMonthly(const Calendar &calendar) {
    auto now = getTimeNow();

    mYear = now->tm_year + 1900;
    mMonth = now->tm_mon + 1;
    mCalendar = calendar;
}

shared_ptr<DisplayCalendar> DisplayMonthly::clone() const {
    return make_shared<DisplayMonthly>(*this);
}
