
#pragma once

#include "CCalendar.h"
#include "CDisplayDaily.h"
#include "CDisplayWeekly.h"
#include "CDisplayMonthly.h"
#include "CEventSimple.h"
#include "CEventRecurring.h"

/**
 * Main class of the program, handles most of the input and output.
 */
class CApplication {
public:
    CApplication();

    /**
     * Asks user whether to initialize an empty calendar or import it from a file
     */
    void handleImport();

    /**
     * Starts the main loop of the calendar application. Prompts user with the main menu. Main menu has options
     * to add, move, remove, display events.
     */
    void displayMainMenu();

    /**
     * Prompts user to add an event. He writes down all of the necessary fields for the event. Detects
     * a conflict if the event already exists.
     *
     * Asks user what to do if the conflict arises. User has an option to choose a different date of the event, or move
     * the existing, calendar event.
     */
    void addEvent();

    /**
     * Moves the existing event to a different date/time using the event id.
     */
    void moveEvent();

    /**
     * Removes the event from the calendar, using the event id.
     */
    void removeEvent();

    /**
     * Finds and prints the events (multiple) based on the search criteria (like datetime, name...). You can also
     * combine these criteria using (OR) or (AND) (not both).
     *
     * Allows user to export the returned results.
     */
    void findEvents();

    /**
     * Displays the calendar using daily, weekly or monthly mode. Allows user to list through the pages of the
     * calendar based on the specified mode (next page, previous page).
     */
    void displayCalendar();

    /**
     * Exports the calendar to a specific file.
     */
    void exportCalendar();

private:
    // different display mode depending on the output of the user
    map<int, shared_ptr<CDisplayCalendar>> calendarDisplayer = {
            {1, CDisplayDaily().clone()},
            {2, CDisplayWeekly().clone()},
            {3, CDisplayMonthly().clone()}
    };
    CCalendar mCalendar;
    size_t mLastEventId;  // used for assigning the ids to the events. Auto increments.
};

