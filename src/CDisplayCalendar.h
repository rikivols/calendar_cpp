
#pragma once

#include <ctime>

#include "CCalendar.h"

/**
 * Base class for the displaying of the calendar.
 */
class CDisplayCalendar {
public:
    virtual ~CDisplayCalendar() noexcept = default;

    [[nodiscard]] virtual shared_ptr<CDisplayCalendar> clone() const = 0;

    /**
     * Sets a calendar to display
     *
     * @param[in] calendar calendar to display
     */
    void setCalendar(const CCalendar &calendar);

    ostream &displayDailyEvents(ostream &out, int year, int month, int day) const;

    [[nodiscard]] static tm *getTimeNow() {
        time_t cTime = time(nullptr);
        return localtime(&cTime);
    }

    static void getNextDay(int &year, int &month, int &day) {
        CDatetime datetime(year, month, day, 0, 0);
        CDatetime tomorrow = datetime + 1440;

        year = tomorrow.getYear();
        month = tomorrow.getMonth();
        day = tomorrow.getDay();
    }

    /**
     * Print out the current page of the calendar.
     */
    virtual void display() const = 0;

    /**
     * Set a new page of the calendar and display it.
     */
    virtual void nextPage() = 0;

    /**
     * Set a previous page of the calendar and display it.
     */
    virtual void previousPage() = 0;

protected:
    CCalendar mCalendar;
    int mYear = 10;
};
