#include <map>

#include "event.h"
#include "datetime.h"


class Calendar {
public:
    Calendar(bool isImport, const string & importFilePath="");

protected:

    map<size_t, shared_ptr<Event>> mEvents;

};
