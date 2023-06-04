
#pragma once

#include <utility>
#include <fstream>

#include "../CCalendar.h"

class CEventExporter {

    explicit CEventExporter(const map<size_t, shared_ptr<CEvent>> &events);

    /**
     * Export the calendar to a CSV - like format
     *
     * @param[in] filePath path of the file we want to export to
     * @return true = export was successful
     *         false = export failed, display the reason
     */
    bool exportToFile(const string &filePath);

private:
    map<size_t, shared_ptr<CEvent>> mEvents;
};
