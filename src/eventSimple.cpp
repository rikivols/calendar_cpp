
#include "eventSimple.h"

#include <utility>

EventSimple::EventSimple(size_t eventId, string name, const Datetime &start, const Datetime &end, string place,
                         const vector<string> &attendees, const vector<string> &tags,
                         string notes): Event(eventId, std::move(name), start, std::move(place), attendees, tags,
                                              std::move(notes)) {
    mEnd = end;
}

shared_ptr<Event> EventSimple::clone() const {
    return std::make_shared<EventSimple>(*this);
}

size_t EventSimple::getId() const {
    return mEventId;
}

