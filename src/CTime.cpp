#include "CDatetime.h"

CTime::CTime(): mMinute(69), mHour(69) {}  // initialize with a value that's not a valid time

CTime::CTime(size_t hour, size_t minute): mHour(hour), mMinute(minute) {}

CTime &CTime::loadTime() {
    cout << "Select hour:" << endl;
    mHour = loadNumber(0, 23);

    cout << "Select minute:" << endl;
    mMinute = loadNumber(0, 59);

    return *this;
}


bool CTime::operator> (const CTime &inp) const {
    if ( this->mHour > inp.mHour ){
        return true;
    }
    if ( this->mHour == inp.mHour ) {
        if ( this->mMinute > inp.mMinute )
            return true;
    }
    return false;
}

bool CTime::operator==(const CTime &inp) const {
    return this->mHour == inp.mHour && this->mMinute == inp.mMinute;
}

bool CTime::operator<(const CTime &inp) const {
    return !(this->operator>(inp)) && !(this->operator==(inp));
}

bool CTime::operator>=(const CTime &inp) const {
    return this->operator==(inp) || this->operator>(inp);
}

bool CTime::operator<=(const CTime &inp) const {
    return this->operator==(inp) || this->operator<(inp);
}

size_t CTime::operator-(const CTime &inp) const {
    size_t resultMinutes = 0;
}

// TODO
CTime CTime::operator+(size_t minutes) const {
    return {};
}

size_t CTime::getHour() const {
    return mHour;
}

size_t CTime::getMinute() const {
    return mMinute;
}
