#include "CDatetime.h"

CDatetime::CDatetime() : mYear(0), mMonth(0), mDay(0), CTime() {}

CDatetime::CDatetime(int year, int month, int day, int hour, int minute) : mYear(year), mMonth(month),
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

bool CDatetime::operator> (const CDatetime & inp) const {

    if ( this->mYear > inp.mYear ) {
        return true;
    }
    if ( this->mYear == inp.mYear ) {
        if ( this->mMonth > inp.mMonth ) {
            return true;
        }
        if ( this->mMonth == inp.mMonth ) {
            if ( this->mDay > inp.mDay ) {
                return true;
            }
            return this->getTime()>(CTime(inp.mHour, inp.mMinute));
        }
    }
    return false;
}

bool CDatetime::operator==(const CDatetime &inp) const {
    return this->mYear == inp.mYear && this->mMonth == inp.mMonth && this->mDay == inp.mDay && this->mHour == inp.mHour
            && this->mMinute == inp.mMinute;
}

bool CDatetime::operator<(const CDatetime &inp) const {
    return !(this->operator>(inp)) && !(this->operator==(inp));
}

bool CDatetime::operator>=(const CDatetime &inp) const {
    return this->operator==(inp) || this->operator>(inp);
}

bool CDatetime::operator<=(const CDatetime &inp) const {
    return this->operator==(inp) || this->operator<(inp);
}

CTime CDatetime::getTime() const {
    return {mHour, mMinute};
}

CDatetime &CDatetime::setTime(const CTime & time) {
    // we need to add 1 day before updating time
    if (this->getTime() > time) {
        *this = this->operator+(1440);
    }
    mHour = time.getHour();
    mMinute = time.getMinute();

    return *this;
}

ostream &CDatetime::printDate(ostream &out) const {
    out << mYear << "." << addZeroPadding(mMonth) << "." << addZeroPadding(mDay);

    return out;
}

std::ostream &operator<<(ostream &out, const CDatetime &self) {

    self.printDate(out) << " ";
    self.printTime(out);

    return out;
}

bool CDatetime::isOnDay(int year, int month, int day) const {
    return mYear == year && mMonth == month && mDay == day;
}

int CDatetime::getYear() const {
    return mYear;
}

int CDatetime::getMonth() const {
    return mMonth;
}

int CDatetime::getDay() const {
    return mDay;
}

CDatetime CDatetime::operator+(int minutes) const {
    auto timeT = getTimeT();
    timeT += minutes;
    CDatetime datetime(timeT);

    return datetime;
}

time_t CDatetime::getTimeT() const {
    struct tm timeStruct;

    timeStruct.tm_year = mYear;
    timeStruct.tm_mon = mMonth;
    timeStruct.tm_mday = mDay;
    timeStruct.tm_hour = mHour;
    timeStruct.tm_min = mMinute;

    time_t timeT = mktime(&timeStruct);

    return timeT;
}

CDatetime::CDatetime(time_t timeT) {
    struct tm timeStruct = *localtime(&timeT);

    mYear = timeStruct.tm_year;
    mMonth = timeStruct.tm_mon;
    mDay = timeStruct.tm_mday;
    mHour = timeStruct.tm_hour;
    mMinute = timeStruct.tm_min;
}
