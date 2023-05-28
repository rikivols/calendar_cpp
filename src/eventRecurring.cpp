
#include "eventRecurring.h"

EventRecurring::EventRecurring(size_t eventId, const string &name, const Datetime &start, const string &place,
                               const vector<string> &attendees, const vector<string> &tags, const string &notes) :
        EventSimple(eventId, name, start, Datetime(0, 0, 0, 0, 0), place, attendees, tags, notes) {}

shared_ptr<Event> EventRecurring::clone() const {
    return std::make_shared<EventRecurring>(*this);
}
