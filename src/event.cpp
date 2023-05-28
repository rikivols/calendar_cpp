#include "event.h"

#include <utility>

std::ostream &operator<<(std::ostream &out, const Event &self) {
    return self.print(out);
}

Event::Event(size_t eventId, string name, const Datetime &start, string place, const vector<string> &attendees,
             const vector<string> &tags, string notes): mEventId(eventId), mName(std::move(name)), mStart(start),
                                                        mPlace(std::move(place)), mAttendees(attendees), mTags(tags),
                                                        mNotes(std::move(notes)) {}

size_t Event::getId() const {
    return mEventId;
}

void Event::setStart(const Datetime &start) {
    mStart = start;
}
