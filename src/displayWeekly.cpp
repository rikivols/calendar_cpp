#include "displayWeekly.h"

DisplayWeekly::DisplayWeekly(const Calendar &calendar) {
    auto now = getTimeNow();

    mYear = now->tm_year + 1900;
    // 0 is if it's an incomplete first week, 1 if first week is a complete week
    mWeek = (now->tm_yday - now->tm_wday + 7) / 7;
    mCalendar = calendar;
}

shared_ptr<DisplayCalendar> DisplayWeekly::clone() const {
    return make_shared<DisplayWeekly>(*this);
}
