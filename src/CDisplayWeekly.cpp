
#include "CDisplayWeekly.h"

/**
 * Store the provided calendar and set the display page to today's week.
 *
 * @param calendar calendar we want to display
 */
CDisplayWeekly::CDisplayWeekly() {
    auto now = getTimeNow();

    mYear = now->tm_year + 1900;
    // 0 is if it's an incomplete first week, 1 if first week is a complete week
    mWeek = (now->tm_yday - now->tm_wday + 7) / 7;
}

shared_ptr<CDisplayCalendar> CDisplayWeekly::clone() const {
    return make_shared<CDisplayWeekly>(*this);
}
