#include "displayMonthly.h"

/**
 * Store the provided calendar and set the display page to today's month.
 *
 * @param calendar calendar we want to display
 */
DisplayMonthly::DisplayMonthly() {
    auto now = getTimeNow();

    mYear = now->tm_year + 1900;
    mMonth = now->tm_mon + 1;
}

shared_ptr<DisplayCalendar> DisplayMonthly::clone() const {
    return make_shared<DisplayMonthly>(*this);
}
