
#pragma once

#include "CDisplayCalendar.h"


/**
 * Displays a calendar in a weekly form, allows user to list the calendar by a week. Each page starts with Monday
 * and ends with Sunday
 */
class CDisplayWeekly : public CDisplayCalendar {
public:
    CDisplayWeekly() = default;

    [[nodiscard]] unique_ptr<CDisplayCalendar> clone() const override;

    /**
    * Updates the current display date to Monday of today's week.
    */
    void refreshCurrentPage() override;

    /**
    * Print out the current weekly page of the calendar.
    */
    void display() const override;

    /**
     * Get the next Monday date and display the weekly page.
     */
    void nextPage() override;

    /**
     * Get the previous Monday date and display the weekly page.
     */
    void previousPage() override;

};