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

        if (isValidDate()) {
            break;
        }
        else {
            cout << "Your date isn't valid, please select your date again." << endl;
        }
    }

    return *this;
}

bool CDatetime::operator> (const CDatetime & inp) const {

    if ( mYear > inp.mYear ) {
        return true;
    }
    if ( mYear == inp.mYear ) {
        if ( mMonth > inp.mMonth ) {
            return true;
        }
        if ( mMonth == inp.mMonth ) {
            if ( mDay > inp.mDay ) {
                return true;
            }
            if (mDay == inp.mDay) {
                return getTime() > (CTime(inp.mHour, inp.mMinute));
            }
        }
    }
    return false;
}

bool CDatetime::operator==(const CDatetime &inp) const {
    return mYear == inp.mYear && mMonth == inp.mMonth && mDay == inp.mDay && mHour == inp.mHour
            && mMinute == inp.mMinute;
}

bool CDatetime::operator<(const CDatetime &inp) const {
    return !(*this > inp) && !(*this == inp);
}

bool CDatetime::operator>=(const CDatetime &inp) const {
    return *this == inp || *this > inp;
}

bool CDatetime::operator<=(const CDatetime &inp) const {
    return *this == inp || *this < inp;
}

CTime CDatetime::getTime() const {
    return {mHour, mMinute};
}

void CDatetime::setTime(const CTime & time) {
    // we need to add 1 day before updating time
    if (time < this->getTime()) {
        *this += DAY_MINUTES;
    }

    mHour = time.getHour();
    mMinute = time.getMinute();
}


CDatetime CDatetime::getDate() const {
    return {mYear, mMonth, mDay, 0, 0};
}


void CDatetime::setDate(int year, int month, int day) {
    mYear = year;
    mMonth = month;
    mDay = day;
    mHour = 12;
    mMinute = 0;
}


int CDatetime::getDaysInAMonth() const {
    CDatetime newDatetime = *this;

    int curDay = 28;

    for ( ; curDay <= 32; curDay++) {
        newDatetime.setDate(mYear, mMonth, curDay);

        if (!newDatetime.isValidDate()) {
            return curDay - 1;
        }
    }

    return 31;
}


void CDatetime::addMonth() {
    mMonth++;
    if (mMonth > 12) {
        mMonth = 1;
        mYear++;
    }
}


void CDatetime::decreaseMonth() {
    mMonth--;
    if (mMonth <= 0) {
        mMonth = 12;
        mYear--;
    }
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

int CDatetime::getWeekDay() const {
    auto timeT = getTimeT();
    auto tm = gmtime(&timeT);

    int weekDay = tm->tm_wday;
    if (weekDay == 0) {
        return 6;
    }
    return weekDay - 1;
}


void CDatetime::setLocalDate(tm * localTime) {
    mYear = localTime->tm_year + 1900;
    mMonth = localTime->tm_mon + 1;
    mDay = localTime->tm_mday;
    mHour = 12;
    mMinute = 0;
}


CDatetime CDatetime::operator+(int minutes) const {
    auto timeT = getTimeT();
    timeT += minutes * 60;
    CDatetime datetime(timeT);

    return datetime;
}


CDatetime &CDatetime::operator+=(int minutes) {
    *this = *this + minutes;
    return *this;
}


CDatetime CDatetime::operator-(int minutes) const {
    return *this + -minutes;
}


CDatetime &CDatetime::operator-=(int minutes) {
    *this = *this - minutes;
    return *this;
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
    timeStruct.tm_year = mYear - 1900; // years are from 1900
    timeStruct.tm_mon = mMonth - 1;    // months are from 0
    timeStruct.tm_mday = mDay;         // days are from 1
    timeStruct.tm_hour = 12;           // set to 12 because of timezones

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


long CDatetime::operator-(const CDatetime &datetime) const {
    auto tm1 = getTimeT();
    auto tm2 = datetime.getTimeT();

    return (tm1 - tm2) / 60;
}

bool CDatetime::isValidDate() const {

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
