
#include "eventSimple.h"

#include <utility>

EventSimple::EventSimple(size_t eventId, const Datetime &start, const Datetime &end, string place,
                         const vector<string> &attendees, const set<string> &tags,
                         const string &notes) : mEventId(eventId), mStart(start), mEnd(end), mPlace(std::move(place)),
                                                mAttendees(attendees), mTags(tags) {}

shared_ptr<Event> EventSimple::clone() const {
    return std::make_shared<EventSimple>(*this);
}

size_t EventSimple::getId() const {
    return mEventId;
}

