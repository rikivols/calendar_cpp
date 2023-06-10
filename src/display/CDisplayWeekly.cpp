
#include "CDisplayWeekly.h"

/**
 * Store the provided calendar and set the display page to today's week.
 *
 * @param calendar calendar we want to display
 */

unique_ptr<CDisplayCalendar> CDisplayWeekly::clone() const {
    return make_unique<CDisplayWeekly>(*this);
}

void CDisplayWeekly::refreshCurrentPage() {
    auto now = getTimeNow();

    mCurrentPage.setLocalDate(now);
    mCurrentPage -= mCurrentPage.getWeekDay() * DAY_MINUTES;
}

void CDisplayWeekly::display() const {
    cout << endl << string(35, '*') << endl;
    cout << endl << "Displaying events for a week: " << stringifyDay(mCurrentPage) << " - "
         << stringifyDay(mCurrentPage + 6 * DAY_MINUTES) << endl;

    for (int i=0; i<7; i++) {
        displayDailyEvents(mCurrentPage + i * DAY_MINUTES, true);
    }
    cout << endl;
    cout << string(35, '*') << endl << endl;
}

void CDisplayWeekly::nextPage() {
    mCurrentPage += DAY_MINUTES * 7;
    display();
}

void CDisplayWeekly::previousPage() {
    mCurrentPage -= DAY_MINUTES * 7;
    display();
}
