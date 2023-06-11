
#pragma once

#include <ctime>

#include "../CCalendar.h"
#include "../utils/CHelpers.h"

/**
 * Base class for the displaying of the calendar. We inherit from this class to display the calendar in various modes
 * (daily, weekly, monthly).
 *
 * It keeps track of the current page that's being explored to be able to list in the calendar.
 */
class CDisplayCalendar {
public:
    virtual ~CDisplayCalendar() noexcept = default;

    [[nodiscard]] virtual unique_ptr<CDisplayCalendar> clone() const = 0;

    /**
     * Sets the newest calendar to display.
     *
     * @param calendar calendar to display
     */
    void setCalendar(const CCalendar &calendar);

    /**
     * Displays the events of a calendar for the given day.
     *
     * @param datetime Date of the events to display
     * @param displaySeparator whether to print the '=' separator between the event days. This separator is used when
     *                         for weekly and monthly display, to have the days visually separated
     */
    void displayDailyEvents(const CDatetime &datetime, bool displaySeparator) const;

    /**
     * Creates a visual representation of the day with the name of the weekday.
     *
     * @param datetime Date to display
     * @return The stringified day to display like - 2020.05.11 (Monday)
     */
    static string stringifyDay(const CDatetime &datetime);

    /**
     * Updates the current date and time for the calendar display. Used before displaying.
     */
    virtual void refreshCurrentPage() = 0;

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
    // current page of the calendar
    CDatetime mCurrentPage;
};
