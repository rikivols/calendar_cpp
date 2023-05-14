
#pragma once

#include <utility>

#include "calendar.h"


class CalendarExporter {

    explicit CalendarExporter(Calendar  calendar);

    /**
     * Export the calendar to a CSV - like format
     *
     * @param filePath path of the file we want to export to
     * @return true = export was successful
     *         false = export failed, display the reason
     */
    bool exportToFile(const string & filePath);

private:
    Calendar mCalendar;
};
