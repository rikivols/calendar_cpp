
#pragma once

#include "../CCalendar.h"

/**
 * Class responsible for importing of the calendar.
 */
class CCalendarImporter {

    CCalendarImporter() = default;

    /**
     * Import the calendar from a CSV - like format
     *
     * @param[in] filePath path of the file we want to import from
     * @return true = import was successful
     *         false = import failed, display the reason
     */
    CCalendar importFromFile(const string &filePath);

};
