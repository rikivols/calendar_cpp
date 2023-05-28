
#include "eventRecurring.h"

EventRecurring::EventRecurring(size_t eventId, string name, const Datetime &start, const Time &end, string place,
                               const vector<string> &attendees, const vector<string> &tags,
                               string notes): Event(eventId, std::move(name), start, std::move(place), attendees, tags,
                                                    std::move(notes)) {
    mEnd = end;
}

shared_ptr<Event> EventRecurring::clone() const {
    return std::make_shared<EventRecurring>(*this);
}
