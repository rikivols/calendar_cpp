#include "CDisplayCalendar.h"

void CDisplayCalendar::setCalendar(const CCalendar &calendar) {
    mCalendar = calendar;
}

ostream &CDisplayCalendar::displayDailyEvents(ostream &out, int year, int month, int day) const {
    auto dailyEvents = mCalendar.getDailyEvents(year, month, day);

    printSeparator(out);
    out << "Date: " << year << "." << month << "." << day;

    for (const auto &event: dailyEvents) {
        out << endl << event << endl;
    }
    printSeparator(out);

    return out;
}
