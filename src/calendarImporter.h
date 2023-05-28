
#pragma once

#include "calendar.h"

/**
 * Class responsible for importing of the calendar.
 */
class CalendarImporter {

    CalendarImporter() = default;

    /**
     * Import the calendar from a CSV - like format
     *
     * @param[in] filePath path of the file we want to import from
     * @return true = import was successful
     *         false = import failed, display the reason
     */
    Calendar importFromFile(const string &filePath);

};