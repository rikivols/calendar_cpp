
#pragma once

#include "../event/CEvent.h"
#include "../utils/CHelpers.h"

#include <utility>
#include <fstream>
#include <map>

class CEventExporter {
public:

    explicit CEventExporter(const vector<shared_ptr<CEvent>> &events);

    /**
     * Export the calendar to a CSV - like format
     *
     * @param[in] filePath path of the file we want to export to
     * @return true = export was successful
     *         false = export failed, display the reason
     */
    void exportToFile(const string &nameOfFile) const;

private:
    vector<shared_ptr<CEvent>> mEvents;
};
