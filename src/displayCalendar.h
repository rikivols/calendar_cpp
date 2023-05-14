
#pragma once

#include <ctime>

#include "calendar.h"

tm *getTimeNow() {
    time_t cTime = time(nullptr);
    return localtime(&cTime);
}

class DisplayCalendar {
public:
    virtual ~DisplayCalendar() noexcept = default;

    [[nodiscard]] virtual shared_ptr<DisplayCalendar> clone() const = 0;

    /**
     * Sets a calendar to display
     *
     * @param calendar calendar to display
     */
    void setCalendar(const Calendar &calendar);

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
    Calendar mCalendar;
    size_t mYear = 10;
};
