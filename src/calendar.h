#include <map>

#include "event.h"
#include "displayCalendar.h"


class Calendar {
public:
    explicit Calendar(bool isImport, const string & importFilePath="");



protected:
    map<size_t, shared_ptr<Event>> mEvents;
    shared_ptr<DisplayCalendar> mCalendarDisplay;
};
