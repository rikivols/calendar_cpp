
#pragma once

#include "CDisplayCalendar.h"


/**
 * Displays a calendar in a daily form, allows user to list the calendar by days.
 */
class CDisplayDaily : public CDisplayCalendar {
public:
    CDisplayDaily() = default;

    [[nodiscard]] unique_ptr<CDisplayCalendar> clone() const override;

    /**
     * Updates the current day for the calendar display. Used before displaying.
     */
    void refreshCurrentPage() override;

    /**
     * Print out the current daily page of the calendar.
     */
    void display() const override;

    /**
     * Set a new - tomorrow's page of the calendar and display it.
     */
    void nextPage() override;

    /**
     * Set a previous day's page of the calendar and display it.
     */
    void previousPage() override;
};