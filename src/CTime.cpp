#include "CDatetime.h"

CTime::CTime(): mMinute(69), mHour(69) {}  // initialize with a value that's not a valid time

CTime::CTime(int hour, int minute): mHour(hour), mMinute(minute) {}

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

int CTime::operator-(const CTime &inp) const {
    int minutes1 = mHour * 60 + mMinute;
    int minutes2 = inp.mHour * 60 + inp.mMinute;

    return minutes1 - minutes2;
}

// TODO
//CTime CTime::addMinutes(int minutes) const {
//    return {};
//}
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

// 13:00 - 16:00
// 16:00 - 13:00
bool CTime::isInRange(const CTime &from, const CTime &to) const {

    bool reverseCase = from > to;  // reverse case is for example from 13:00 to 1:30

    if (reverseCase) {
        return *this >= from || *this <= to;
    }

    return *this >= from && *this <= to;
}
