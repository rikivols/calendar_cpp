#include "CDisplayMonthly.h"

/**
 * Store the provided calendar and set the display page to today's month.
 *
 * @param calendar calendar we want to display
 */

shared_ptr<CDisplayCalendar> CDisplayMonthly::clone() const {
    return make_shared<CDisplayMonthly>(*this);
}

void CDisplayMonthly::refreshCurrentPage() {
    auto now = getTimeNow();
    mCurrentPage.setDate(now->tm_year, now->tm_mon, 1);
}

void CDisplayMonthly::display() const {
    cout << endl << string(35, '*') << endl;
    cout << endl << "Displaying events for a week: " << stringifyDay(mCurrentPage) << " - "
         << stringifyDay(mCurrentPage + 6);
    for (int i=0; i<7; i++) {
        displayDailyEvents(mCurrentPage+i, false);
    }
    cout << endl;
    cout << string(35, '*') << endl << endl;
}

void CDisplayMonthly::nextPage() {
    mCurrentPage.addMonth();
    display();
}

void CDisplayMonthly::previousPage() {
    mCurrentPage.decreaseMonth();
    display();
}
