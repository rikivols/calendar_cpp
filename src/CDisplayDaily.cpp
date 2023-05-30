
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

void CDisplayDaily::display() const {
    cout << "Displaying events from day: " << stringifyDay(mYear, mMonth, mDay) << ":\n" << endl;
    displayDailyEvents(cout, mYear, mMonth, mDay);
    cout << endl;
}

void CDisplayDaily::nextPage() {
    getNextDay(mYear, mMonth, mDay);

    display();
}

void CDisplayDaily::previousPage() {
    CDatetime datetime(mYear, mMonth, mDay, 0, 0);
    CDatetime tomorrow = datetime - 1440;

    mYear = tomorrow.getYear();
    mMonth = tomorrow.getMonth();
    mDay = tomorrow.getDay();

    display();
}
