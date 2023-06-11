
#include "CDisplayCalendar.h"


void CDisplayCalendar::setCalendar(const CCalendar &calendar) {
    mCalendar = calendar;
}


void CDisplayCalendar::displayDailyEvents(const CDatetime &datetime, bool displaySeparator) const {
    auto dailyEvents = mCalendar.getDailyEvents(datetime.getYear(), datetime.getMonth(), datetime.getDay());

    if (displaySeparator) {
        cout << endl << endl << stringifyDay(datetime);
        printSeparator(cout, '=');
    }

    if (dailyEvents.empty()) {
        cout << endl << "No events" << endl;
    }

    for (const auto &event: dailyEvents) {
        cout << endl << *event << endl;
    }

    if (displaySeparator) {
        printSeparator(cout, '=');
        cout << endl;
    }
}


string CDisplayCalendar::stringifyDay(const CDatetime &datetime) {
    map<int, string> days {
            {0, "Monday"},
            {1, "Tuesday"},
            {2, "Wednesday"},
            {3, "Thursday"},
            {4, "Friday"},
            {5, "Saturday"},
            {6, "Sunday"},
    };

    return addZeroPadding(datetime.getYear()) + "." + addZeroPadding(datetime.getMonth()) + "." +
           addZeroPadding(datetime.getDay()) + " (" + days[datetime.getWeekDay()] + ")";
}
