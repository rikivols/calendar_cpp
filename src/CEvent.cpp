#include "CEvent.h"

#include <utility>

std::ostream &operator<<(std::ostream &out, const CEvent &self) {
    return self.print(out);
}

CEvent::CEvent(size_t eventId, string name, const CDatetime &start, string place, const vector<string> &attendees,
             const vector<string> &tags, string notes): mEventId(eventId), mName(std::move(name)), mStart(start),
                                                        mPlace(std::move(place)), mAttendees(attendees), mTags(tags),
                                                        mNotes(std::move(notes)) {}

size_t CEvent::getId() const {
    return mEventId;
}

void CEvent::setStart(const CDatetime &start) {
    mStart = start;
}

CDatetime CEvent::getStart() const {
    return mStart;
}
