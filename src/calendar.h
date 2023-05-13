#include <map>

#include "event.h"


class Calendar {
public:
    explicit Calendar(bool isImport=false, const string & importFilePath="");

    bool addEvent(const shared_ptr<Event> &event);

    bool moveEvent(size_t hours);

    bool removeEvent(size_t eventId);

    const vector<shared_ptr<Event>> &findEvents(const Datetime &before, const Datetime &after, const string &place,
                                                const vector<string> &attendees, const set<string> &tags, bool isAnd);

protected:
    map<size_t, shared_ptr<Event>> mEvents;
};
