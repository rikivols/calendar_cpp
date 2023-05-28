#include "datetime.h"

Datetime::Datetime() : mYear(-1), mMonth(-1), mDay(-1), mHour(-1), mMinute(-1) {}

Datetime::Datetime(size_t year, size_t month, size_t day, size_t hour, size_t minute) : mYear(year), mMonth(month),
                                                                                        mDay(day), mHour(hour),
                                                                                        mMinute(minute) {}

Datetime &Datetime::loadDatetime(bool skipDate) {

    while (true) {
        if (skipDate) {
            mYear = mMonth = mDay = -1;
        } else {
            cout << "Select year:" << endl;
            mYear = loadNumber(1990, 2100);

            cout << "Select month:" << endl;
            mMonth = loadNumber(1, 12);

            cout << "Select day:" << endl;
            mDay = loadNumber(1, 31);
        }

        cout << "Select hour:" << endl;
        mHour = loadNumber(0, 23);

        cout << "Select minute:" << endl;
        mMinute = loadNumber(0, 59);

        if (this->isValid()) {
            break;
        }
        else {
            // is valid will comment why
            cout << "please select again" << endl;
        }
    }

    return *this;
}
