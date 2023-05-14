
#include "displayDaily.h"

/**
 * Store the provided calendar and set the display page to today.
 *
 * @param calendar calendar we want to display
 */
DisplayDaily::DisplayDaily() {
    auto now = getTimeNow();

    mYear = now->tm_year + 1900;
    mMonth = now->tm_mon + 1;
    mDay = now->tm_mday;
}

shared_ptr<DisplayCalendar> DisplayDaily::clone() const {
    return make_shared<DisplayDaily>(*this);
}
