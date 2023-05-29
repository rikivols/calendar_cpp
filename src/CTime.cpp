#include "CDatetime.h"

CTime::CTime(): mMinute(-1), mHour(-1) {}

CTime::CTime(size_t hour, size_t minute): mHour(hour), mMinute(minute) {}

CTime &CTime::loadTime() {
    cout << "Select hour:" << endl;
    mHour = loadNumber(0, 23);

    cout << "Select minute:" << endl;
    mMinute = loadNumber(0, 59);

    return *this;
}