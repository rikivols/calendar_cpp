#include "CDatetime.h"

CDatetime::CDatetime() : CTime(), mYear(0), mMonth(0), mDay(0) {}

CDatetime::CDatetime(int year, int month, int day, int hour, int minute) : CTime(hour, minute), mYear(year),
                                                                           mMonth(month), mDay(day) {}

CDatetime &CDatetime::loadDatetime() {

    while (true) {

        cout << "Select year: ";
        mYear = loadNumber(1990, 2100);

        cout << "Select month: ";
        mMonth = loadNumber(1, 12);

        cout << "Select day: ";
        mDay = loadNumber(1, 31);

        loadTime();

        if (this->isValidDate()) {
            break;
        }
        else {
            cout << "Your date isn't valid, please select your date again." << endl;
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

string CDatetime::toString() const {
    return to_string(mYear) + "." + addZeroPadding(mMonth) + "." + addZeroPadding(mDay) + " " + toStringTime();
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
    timeT += minutes * 60;
    CDatetime datetime(timeT);

    return datetime;
}

time_t CDatetime::getTimeT() const {
    struct tm timeStruct = {0};

    timeStruct.tm_year = mYear - 1900;
    timeStruct.tm_mon = mMonth - 1;
    timeStruct.tm_mday = mDay;
    timeStruct.tm_hour = mHour;
    timeStruct.tm_min = mMinute;

    return mktime(&timeStruct) - timezone;  // work with UTC
}

tm CDatetime::getTmDate() const {
    struct tm timeStruct = {0};
    timeStruct.tm_year = mYear - 1900; // years count from 1900
    timeStruct.tm_mon = mMonth - 1;    // months count from January=0
    timeStruct.tm_mday = mDay;         // days count from 1
    timeStruct.tm_hour = 12;           // set to 12 in case we have an hour shift because of the different timezones

    return timeStruct;
}

CDatetime::CDatetime(time_t timeT) {
    struct tm timeStruct = *gmtime(&timeT);  // work with UTC

    mYear = timeStruct.tm_year + 1900;
    mMonth = timeStruct.tm_mon + 1;
    mDay = timeStruct.tm_mday;
    mHour = timeStruct.tm_hour;
    mMinute = timeStruct.tm_min;
}

CDatetime CDatetime::operator-(int minutes) const {
    return *this + -minutes;
}

long CDatetime::operator-(const CDatetime &datetime) const {
    auto tm1 = getTimeT();
    auto tm2 = datetime.getTimeT();

    return (tm1 - tm2) / 60;
}

bool CDatetime::isValidDate() {

    if (mYear < 1990 || mYear > 2100 || mMonth <= 0 || mMonth > 12 || mDay <= 0 || mDay > 31) {
        return false;
    }

    auto originalTime = getTmDate();
    auto copyOfTime = originalTime;

    auto temporaryTime = mktime(&copyOfTime);
    copyOfTime = *localtime(&temporaryTime);

    if (copyOfTime.tm_year != originalTime.tm_year || copyOfTime.tm_mon != originalTime.tm_mon ||
            copyOfTime.tm_mday != originalTime.tm_mday) {
        return false;
    }

    return isValidTime();
}


//CDatetime CDatetime::operator+(const CDatetime &datetime) const {
//    return CDatetime();
//}
