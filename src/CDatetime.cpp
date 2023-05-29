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
