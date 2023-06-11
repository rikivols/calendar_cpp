
#pragma once

#include "CDisplayCalendar.h"


/**
 * Displays a calendar in a monthly form, allows user to list the calendar by a month. Each page starts with the 1st day
 * of the month to the last day of the month
 */
class CDisplayMonthly : public CDisplayCalendar {
public:
    CDisplayMonthly() = default;

    [[nodiscard]] unique_ptr<CDisplayCalendar> clone() const override;

    /**
     * Updates the current month for the calendar display. Used before displaying.
     */
    void refreshCurrentPage() override;

    /**
     * Print out the current monthly page of the calendar.
     */
    void display() const override;

    /**
     * Get the next month page and display it.
     */
    void nextPage() override;

    /**
     * Get the previous month page and display it.
     */
    void previousPage() override;
};