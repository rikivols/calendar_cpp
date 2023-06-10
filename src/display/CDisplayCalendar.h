
#pragma once

#include <ctime>

#include "../CCalendar.h"
#include "../utils/CHelpers.h"

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

    void displayDailyEvents(const CDatetime &datetime, bool displaySeparator) const;

    static string stringifyDay(const CDatetime &datetime);

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
    CDatetime mCurrentPage;
};
