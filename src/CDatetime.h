
#pragma once

#include <ctime>
#include <iostream>

#include "CHelpers.h"

using namespace std;

/**
 * Class that represents the date and the time of the events
 */

class CTime {
public:
    CTime();

    CTime(size_t hour, size_t minute);

    bool isValidTime();

    // TODO
    bool isInRange(const CTime &from, const CTime &to) const;

    bool operator> (const CTime &inp) const;

    bool operator== (const CTime & inp) const;

    bool operator< (const CTime & inp) const;

    bool operator<= (const CTime & inp) const;

    bool operator>= (const CTime & inp) const;

    size_t operator- (const CTime & inp) const;

    CTime & loadTime();

    size_t getHour() const;

    size_t getMinute() const;

    CTime operator+ (size_t minutes) const;

    ostream &printTime(ostream &out) const;

    friend std::ostream &operator<<(std::ostream &out, const CTime &self);


protected:
    size_t mHour;
    size_t mMinute;
};


class CDatetime: public CTime {
public:

    CDatetime();

    CDatetime(size_t year, size_t month, size_t day, size_t hour, size_t minute);

    /**
     * Find out whether the datetime is a correct date and time.
     *
     * @return true = correct datetime, false = incorrect
     */
    bool isValidDate();

    /**
     * Find out whether the datetime belongs to the provided range
     *
     * @param[in] from start of the range that datetime should belong to
     * @param[in] to end of the range that datetime should belong to
     * @return true = datetime belongs to the range, false = doesn't
     */
    bool isInRange(const CDatetime &from, const CDatetime &to);

    CTime getTime() const;

    bool operator> (const CDatetime & inp) const;

    bool operator== (const CDatetime & inp) const;

    bool operator< (const CDatetime & inp) const;

    bool operator<= (const CDatetime & inp) const;

    bool operator>= (const CDatetime & inp) const;

    CDatetime operator+ (size_t minutes) const;

    CDatetime & setTime(const CTime &time);

    CDatetime & loadDatetime();

    ostream &printDate(ostream &out) const;

    friend std::ostream &operator<<(std::ostream &out, const CDatetime &self);

private:
    size_t mYear;
    size_t mMonth;
    size_t mDay;
};
