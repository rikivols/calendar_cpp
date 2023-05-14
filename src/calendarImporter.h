
#pragma once

#include "calendar.h"

class CalendarImporter {

    CalendarImporter();

    /**
     * Import the calendar from a CSV - like format
     *
     * @param filePath path of the file we want to import from
     * @return true = import was successful
     *         false = import failed, display the reason
     */
    Calendar importFromFile(const string &filePath);

};
