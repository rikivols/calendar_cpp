
#include "CDisplayDaily.h"

/**
 * Store the provided calendar and set the display page to today.
 *
 * @param calendar calendar we want to display
 */
CDisplayDaily::CDisplayDaily() {
    auto now = getTimeNow();

    mYear = now->tm_year + 1900;
    mMonth = now->tm_mon + 1;
    mDay = now->tm_mday;
}

shared_ptr<CDisplayCalendar> CDisplayDaily::clone() const {
    return make_shared<CDisplayDaily>(*this);
}
