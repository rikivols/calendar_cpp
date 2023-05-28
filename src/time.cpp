#include "datetime.h"

Time::Time(): mMinute(-1), mHour(-1) {}

Time::Time(size_t hour, size_t minute): mHour(hour), mMinute(minute) {}

Time &Time::loadTime() {
    cout << "Select hour:" << endl;
    mHour = loadNumber(0, 23);

    cout << "Select minute:" << endl;
    mMinute = loadNumber(0, 59);

    return *this;
}