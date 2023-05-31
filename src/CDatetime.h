
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

    CTime(int hour, int minute);

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

    [[nodiscard]] int getHour() const;

    [[nodiscard]] int getMinute() const;

    CTime operator+ (size_t durationMinutes) const;

    ostream &printTime(ostream &out) const;

    friend std::ostream &operator<<(std::ostream &out, const CTime &self);


protected:
    int mHour;
    int mMinute;
};


class CDatetime: public CTime {
public:

    CDatetime();

    CDatetime(int year, int month, int day, int hour, int minute);

    CDatetime(time_t timeT);

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

    [[nodiscard]] time_t getTimeT() const;

    [[nodiscard]] bool isOnDay(int year, int month, int day) const;

    CDatetime operator+ (int minutes) const;

    CDatetime operator- (int minutes) const;

    [[nodiscard]] int getYear() const;

    [[nodiscard]] int getMonth() const;

    [[nodiscard]] int getDay() const;

    CDatetime & setTime(const CTime &time);

    CDatetime & loadDatetime();

    ostream &printDate(ostream &out) const;

    friend std::ostream &operator<<(std::ostream &out, const CDatetime &self);

private:
    int mYear;
    int mMonth;
    int mDay;
};
