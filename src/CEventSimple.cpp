
#include "CEventSimple.h"

#include <utility>

CEventSimple::CEventSimple(size_t eventId, string name, const CDatetime &start, const CDatetime &end, string place,
                         const vector<string> &attendees, const vector<string> &tags,
                         string notes): CEvent(eventId, std::move(name), start, std::move(place), attendees, tags,
                                              std::move(notes)) {
    mEnd = end;
}

shared_ptr<CEvent> CEventSimple::clone() const {
    return std::make_shared<CEventSimple>(*this);
}

CDatetime CEventSimple::getEnd() const {
    return mEnd;
}

pair<CTime, CTime> CEventSimple::getForeverBusyTime() const {
    return {CTime(), CTime()};
}

CTime CEventSimple::getEndTime() const {
    return getEnd().getTime();
}

size_t CEventSimple::getEventDuration() const {
    return mEnd - mStart;
}

void CEventSimple::setEnd(const CDatetime &end) {
    mEnd = end;
}

//CEventSimple::CEventSimple(const CEventSimple &eventSimple): CEvent(eventSimple) {
//    mEnd = eventSimple.mEnd;
//}
//
//CEventSimple &CEventSimple::operator=(CEventSimple eventSimple) {
//    swapEvent(eventSimple);
//    swap(mEnd, eventSimple.mEnd);
//
//    return *this;
//}
