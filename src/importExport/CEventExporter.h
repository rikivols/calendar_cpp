
#pragma once

#include "../event/CEvent.h"
#include "../utils/CHelpers.h"

#include <utility>
#include <fstream>
#include <map>


/**
 * Class responsible for exporting of the calendar to a file.
 */
class CEventExporter {
public:

    /**
     * Stores the given events and sorts them by the event id to have a prettier export.
     *
     * @param events events to export.
     */
    explicit CEventExporter(const vector<shared_ptr<CEvent>> &events);

    /**
     * Export the calendar to a CSV - like format. All event's properties are separated by the  ',' and array
     * properties are enclosed in the '[]'
     *
     * @param nameOfFile we're storing the export to the assets/ folder. Then the file name will start by this string
     *                   and ends with the current datetime
     */
    void exportToFile(const string &nameOfFile) const;

private:
    vector<shared_ptr<CEvent>> mEvents;
};
