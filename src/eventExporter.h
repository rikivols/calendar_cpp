
#pragma once

#include <utility>

#include "calendar.h"

class EventExporter {

    explicit EventExporter(const map<size_t, shared_ptr<Event>> &events);

    /**
     * Export the calendar to a CSV - like format
     *
     * @param[in] filePath path of the file we want to export to
     * @return true = export was successful
     *         false = export failed, display the reason
     */
    bool exportToFile(const string &filePath);

private:
    map<size_t, shared_ptr<Event>> mEvents;
};
