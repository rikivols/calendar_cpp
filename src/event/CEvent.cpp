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


bool CEvent::nameEquals(const string &name) {
    return mName == name;
}


bool CEvent::placeEquals(const string &place) {
    return mPlace == place;
}


bool CEvent::isInAttendees(const vector<string> &attendees) {
    return isInVector(attendees, mAttendees);
}


bool CEvent::isInTags(const vector<string> &tags) {
    return isInVector(tags, mTags);
}



bool CEvent::sortEventsByStartDatetime(const shared_ptr<CEvent> &event1, const shared_ptr<CEvent> &event2) {
    return event1->getStart() < event2->getStart();
}

CEvent::CEvent(const CEvent &event) {
    mEventId = event.mEventId;
    mName = event.mName;
    mStart = event.mStart;
    mPlace = event.mPlace;

    for (const auto &attendee: event.mAttendees) {
        mAttendees.push_back(attendee);
    }

    for (const auto &tag: event.mTags) {
        mTags.push_back(tag);
    }

    mNotes = event.mNotes;
}

void CEvent::swapEvent(CEvent &event) {
    swap(mEventId, event.mEventId);
    swap(mName, event.mName);
    swap(mStart, event.mStart);
    swap(mPlace, event.mPlace);
    swap(mAttendees, event.mAttendees);
    swap(mTags, event.mTags);
    swap(mNotes, event.mNotes);
}

ostream &CEvent::partialPrint(ostream &out) const {
    out << "Name: " << mName << endl;
    out << "Place: " << mPlace << endl;
    out << "Attendees:" << endl;
    printVector(out, mAttendees);
    out << "Tags:" << endl;
    printVector(out, mTags);
    out << "Notes: " << mNotes;
    printSeparator(out);

    return out;
}


bool CEvent::sortEventsById(const shared_ptr<CEvent> &event1, const shared_ptr<CEvent> &event2) {
    return event1->getId() < event2->getId();
}
