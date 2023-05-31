
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

    bool isValidTime() const;

    // TODO
    [[nodiscard]] bool isInRange(const CTime &from, const CTime &to) const;

    bool operator> (const CTime &inp) const;

    bool operator== (const CTime & inp) const;

    bool operator< (const CTime & inp) const;

    bool operator<= (const CTime & inp) const;

    bool operator>= (const CTime & inp) const;

    int operator- (const CTime & inp) const;

    CTime & loadTime();

    [[nodiscard]] int getHour() const;

    [[nodiscard]] int getMinute() const;

    [[nodiscard]] CTime addMinutes(int durationMinutes) const;

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

    explicit CDatetime(time_t timeT);

    /**
     * Find out whether the datetime is a correct date and time.
     *
     * @return true = correct datetime, false = incorrect
     */
    bool isValidDate();

    [[nodiscard]] CTime getTime() const;

    bool operator> (const CDatetime & inp) const;

    bool operator== (const CDatetime & inp) const;

    bool operator< (const CDatetime & inp) const;

    bool operator<= (const CDatetime & inp) const;

    bool operator>= (const CDatetime & inp) const;

    [[nodiscard]] time_t getTimeT() const;

    [[nodiscard]] tm getTmDate() const;

    [[nodiscard]] bool isOnDay(int year, int month, int day) const;

    CDatetime operator+ (int minutes) const;

    CDatetime operator- (int minutes) const;

    long operator- (const CDatetime &datetime) const;

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
