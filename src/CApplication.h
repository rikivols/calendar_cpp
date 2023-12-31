
#pragma once

#include "CCalendar.h"
#include "display/CDisplayDaily.h"
#include "display/CDisplayWeekly.h"
#include "display/CDisplayMonthly.h"
#include "event/CEventSimple.h"
#include "event/CEventRecurring.h"
#include "CConflictSolver.h"
#include "importExport/CEventExporter.h"
#include "importExport/CCalendarImporter.h"
#include "CCalendarFinder.h"


/**
 * Main class of the program, handles most of the input and output.
 */
class CApplication {
public:
    CApplication();

    /**
     * Asks user whether to initialize an empty calendar or import it from a file
     */
    bool handleImport();

    /**
     * Starts the main loop of the calendar application. Prompts user with the main menu. Main menu has options
     * to add, move, remove, display events...
     */
    void displayMainMenu();

    /**
     * Prompts user to add an event. He writes down all of the necessary fields for the event. Detects
     * a conflict if the event already exists.
     *
     * Asks user what to do if the conflict arises. User has an option to move the new event to the closest date or move
     * the underlying event to the closest day
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

    void getEventById();

private:
    // different display mode depending on the output of the user, 1=daily, 2=weekly, 3=monthly
    map<int, unique_ptr<CDisplayCalendar>> calendarDisplayer;
    CCalendar mCalendar;
    size_t mLastEventId;  // used for assigning the ids to the events. Auto increments.
};

