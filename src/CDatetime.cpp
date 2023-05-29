#include "CDatetime.h"

CDatetime::CDatetime() : mYear(-1), mMonth(-1), mDay(-1), CTime() {}

CDatetime::CDatetime(size_t year, size_t month, size_t day, size_t hour, size_t minute) : mYear(year), mMonth(month),
                                                                                        mDay(day), CTime(hour, minute) {}

CDatetime &CDatetime::loadDatetime() {

    while (true) {

        cout << "Select year:" << endl;
        mYear = loadNumber(1990, 2100);

        cout << "Select month:" << endl;
        mMonth = loadNumber(1, 12);

        cout << "Select day:" << endl;
        mDay = loadNumber(1, 31);

        loadTime();

        if (this->isValidDate()) {
            break;
        }
        else {
            // is valid will comment why
            cout << "please select again" << endl;
        }
    }

    return *this;
}
