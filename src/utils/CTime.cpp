#include "CDatetime.h"

CTime::CTime(): mHour(69), mMinute(69) {}  // initialize with a value that's not a valid time

CTime::CTime(int hour, int minute): mHour(hour), mMinute(minute) {}

CTime &CTime::loadTime() {
    cout << "Select hour: ";
    mHour = loadNumber(0, 23);

    cout << "Select minute: ";
    mMinute = loadNumber(0, 59);

    return *this;
}


bool CTime::operator> (const CTime &inp) const {
    if ( mHour > inp.mHour ){
        return true;
    }
    if ( mHour == inp.mHour ) {
        return mMinute > inp.mMinute;
    }
    return false;
}

bool CTime::operator==(const CTime &inp) const {
    return mHour == inp.mHour && mMinute == inp.mMinute;
}

bool CTime::operator<(const CTime &inp) const {
    return !(*this > inp) && !(*this == inp);
}

bool CTime::operator>=(const CTime &inp) const {
    return *this == inp || *this > inp;
}

bool CTime::operator<=(const CTime &inp) const {
    return *this == inp || *this < inp;
}

int CTime::operator-(const CTime &inp) const {
    int minutes1 = mHour * 60 + mMinute;
    int minutes2 = inp.mHour * 60 + inp.mMinute;

    return minutes1 - minutes2;
}


CTime CTime::addMinutes(int durationMinutes) const {
    // convert all to minutes
    int minutes = mHour * 60 + mMinute;
    minutes += durationMinutes;

    int hour = (minutes / 60) % 24;
    int minute = minutes % 60;

    return {hour, minute};
}


int CTime::getHour() const {
    return mHour;
}

int CTime::getMinute() const {
    return mMinute;
}

ostream &CTime::printTime(ostream &out) const {
    out << addZeroPadding(mHour) << ":" << addZeroPadding(mMinute);

    return out;
}

std::ostream &operator<<(ostream &out, const CTime &self) {
    return self.printTime(out);
}

bool CTime::isInRange(const CTime &from, const CTime &to) const {

    bool reverseCase = from > to;  // reverse case is for example from 13:00 to 1:30

    if (reverseCase) {
        return *this >= from || *this <= to;
    }

    return *this >= from && *this <= to;
}

bool CTime::isValidTime() const {
    return mHour >= 0 && mHour <= 23 && mMinute >= 0 && mMinute <= 59;
}

string CTime::toStringTime() const {
    return addZeroPadding(mHour) + ":" + addZeroPadding(mMinute);
}
