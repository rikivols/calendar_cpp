
#pragma once

#include "calendar.h"
#include "displayDaily.h"
#include "displayWeekly.h"
#include "displayMonthly.h"
#include "eventSimple.h"
#include "eventRecurring.h"

/**
 * Main class of the program, handles most of the input and output.
 */
class Application {
public:
    Application();

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

    int getUserOption(int maxChoice);

private:
    // different display mode depending on the output of the user
    map<int, shared_ptr<DisplayCalendar>> calendarDisplayer = {
            {1, DisplayDaily().clone()},
            {2, DisplayWeekly().clone()},
            {3, DisplayMonthly().clone()}
    };
    Calendar mCalendar;
    size_t lastEventId;  // used for assigning the ids to the events. Auto increments.
};

