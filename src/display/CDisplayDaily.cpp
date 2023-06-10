
#include "CDisplayDaily.h"

/**
 * Store the provided calendar and set the display page to today.
 *
 * @param calendar calendar we want to display
 */

unique_ptr<CDisplayCalendar> CDisplayDaily::clone() const {
    return make_unique<CDisplayDaily>(*this);
}

void CDisplayDaily::refreshCurrentPage() {
    auto now = getTimeNow();
    mCurrentPage.setLocalDate(now);
}


void CDisplayDaily::display() const {
    cout << endl << string(35, '*') << endl;
    cout << endl << "Displaying events on day " << stringifyDay(mCurrentPage) << ":" << endl;
    displayDailyEvents(mCurrentPage, false);
    cout << endl;
    cout << string(35, '*') << endl << endl;
}

void CDisplayDaily::nextPage() {
    mCurrentPage += DAY_MINUTES;

    display();
}

void CDisplayDaily::previousPage() {
    mCurrentPage -= DAY_MINUTES;

    display();
}
