#include "CDisplayCalendar.h"

void CDisplayCalendar::setCalendar(const CCalendar &calendar) {
    mCalendar = calendar;
}

ostream &CDisplayCalendar::displayDailyEvents(ostream &out, int year, int month, int day) const {
    auto dailyEvents = mCalendar.getDailyEvents(year, month, day);
    cout << "Daily events size: " << dailyEvents.size() << endl;

//    printSeparator(out, '=');
    if (dailyEvents.empty()) {
        cout << "No events" << endl;
    }
    else {
        out << endl << stringifyDay(year, month, day);
    }

    for (const auto &event: dailyEvents) {
        out << endl << *event << endl;
    }
//    printSeparator(out, '=');

    return out;
}
