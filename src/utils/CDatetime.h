/**
 * This file contains both event's date and time.
 */


#pragma once

#include <ctime>
#include <iostream>

#include "CHelpers.h"

using namespace std;

#define DAY_MINUTES 1440


/**
 * Class that represents the time of the event.
 */
class CTime {
public:
    CTime();

    CTime(int hour, int minute);

    ostream &printTime(ostream &out) const;

    [[nodiscard]] int getHour() const;

    [[nodiscard]] int getMinute() const;

    /**
     * Checks if time values are out of range.
     *
     * @return true = time is ok false = isn't
     */
    [[nodiscard]] bool isValidTime() const;

    /**
     * Checks if our time is between the given from and to times including equals. We also take into the account the
     * reverse range, where to is bigger than from. In that case we check if the value isn't between.
     *
     * @param from from part of the range
     * @param to to part of the range
     * @return true = time is in a given range, false = isn't
     */
    [[nodiscard]] bool isInRange(const CTime &from, const CTime &to) const;

    bool operator> (const CTime &inp) const;

    bool operator== (const CTime & inp) const;

    bool operator!=(const CTime &inp) const;

    bool operator< (const CTime & inp) const;

    bool operator<= (const CTime & inp) const;

    bool operator>= (const CTime & inp) const;

    int operator- (const CTime & inp) const;

    /**
     * Loads the time from console.
     *
     * @return the newly loaded time
     */
    CTime & loadTime();

    /**
     * Add minutes to the time.
     *
     * @param durationMinutes how many minutes to add
     * @return newly added time
     */
    [[nodiscard]] CTime addMinutes(int durationMinutes) const;

    [[nodiscard]] string toStringTime() const;

    friend std::ostream &operator<<(std::ostream &out, const CTime &self);


protected:
    int mHour;
    int mMinute;
};


/**
 * Class that represents both date and time of the event
 */
class CDatetime: public CTime {
public:

    CDatetime();

    CDatetime(int year, int month, int day, int hour, int minute);

    /**
     * Load datetime from a time_t format without a timezone influence.
     *
     * @param timeT time_t to load from
     */
    explicit CDatetime(time_t timeT);

    ostream &printDate(ostream &out) const;

    /**
     * Gets time of the event as a CTime class
     *
     * @return time of the event.
     */
    [[nodiscard]] CTime getTime() const;

    /**
     * Gets time_t of the datetime without timezone attached.
     *
     * @return time_t of the datetime
     */
    [[nodiscard]] time_t getTimeT() const;

    /**
     * Gets tm struct of the datetime's date with hours set as 12 (to avoid timezone collisions)
     *
     * @return tm struct of the datetime's date
     */
    [[nodiscard]] tm getTmDate() const;

    [[nodiscard]] int getYear() const;

    [[nodiscard]] int getMonth() const;

    [[nodiscard]] int getDay() const;

    /**
     * Get a weekday of the datetime's date. 0 is Monday, 6 is Sunday.
     *
     * @return weekday of the datetime's date
     */
    [[nodiscard]] int getWeekDay() const;

    /**
     * Get only date of the datetime with hours and minutes set as 0
     *
     * @return date of the datetime
     */
    [[nodiscard]] CDatetime getDate() const;

    [[nodiscard]] int getDaysInAMonth() const;

    void setTime(const CTime &time);

    /**
     * Sets a date out of the given tm struct, sets hours as 12.
     *
     * @param localTime tm struct to set the date based on.
     */
    void setLocalDate(tm * localTime);

    /**
     * Sets event's date and sets hours as 12
     *
     * @param year year to set
     * @param month month to set
     * @param day day to set
     */
    void setDate(int year, int month, int day);

    bool operator> (const CDatetime & inp) const;

    bool operator== (const CDatetime & inp) const;

    bool operator< (const CDatetime & inp) const;

    bool operator<= (const CDatetime & inp) const;

    bool operator>= (const CDatetime & inp) const;

    CDatetime operator+ (int minutes) const;

    CDatetime &operator+= (int minutes);

    CDatetime operator- (int minutes) const;

    CDatetime &operator-= (int minutes);

    long operator- (const CDatetime &datetime) const;

    /**
     * Find out whether the datetime is a correct date and time.
     *
     * @return true = correct datetime, false = incorrect
     */
    [[nodiscard]] bool isValidDate() const;

    void addMonth();

    void decreaseMonth();

    /**
     * Loads the time from console.
     *
     * @return the newly loaded time
     */
    CDatetime & loadDatetime();

    /**
     * Converts datetime to a string.
     *
     * @return datetime as a string.
     */
    [[nodiscard]] string toString() const;

    friend std::ostream &operator<<(std::ostream &out, const CDatetime &self);

private:
    int mYear;
    int mMonth;
    int mDay;
};
