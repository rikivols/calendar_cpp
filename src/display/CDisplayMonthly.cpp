
#include "CDisplayMonthly.h"


unique_ptr<CDisplayCalendar> CDisplayMonthly::clone() const {
    return make_unique<CDisplayMonthly>(*this);
}


void CDisplayMonthly::refreshCurrentPage() {
    auto now = getTimeNow();
    mCurrentPage.setDate(now->tm_year + 1900, now->tm_mon + 1, 1);
}


void CDisplayMonthly::display() const {
    cout << endl << string(35, '*') << endl;
    int daysInMonth = mCurrentPage.getDaysInAMonth();

    cout << endl << "Displaying events for a month: " << stringifyDay(mCurrentPage) << " - "
         << stringifyDay(mCurrentPage + (daysInMonth - 1) * DAY_MINUTES) << endl;

    for (int i = 0; i < daysInMonth; i++) {
        displayDailyEvents(mCurrentPage + i * DAY_MINUTES, true);
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
