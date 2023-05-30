
#include "CEventRecurring.h"

CEventRecurring::CEventRecurring(size_t eventId, string name, const CDatetime &start, const CTime &end, string place,
                               const vector<string> &attendees, const vector<string> &tags,
                               string notes): CEvent(eventId, std::move(name), start, std::move(place), attendees, tags,
                                                    std::move(notes)) {
    mEnd = end;
}

shared_ptr<CEvent> CEventRecurring::clone() const {
    return std::make_shared<CEventRecurring>(*this);
}

bool CEventRecurring::isConflict(const CEvent & event, int offset) const {
    return false;
}

ostream &CEventRecurring::print(ostream &out) const {
    return out;
}

CDatetime CEventRecurring::getEnd() const {
    return {0, 0, 0, mEnd.getHour(), mEnd.getMinute()};
}

pair<CTime, CTime> CEventRecurring::getForeverBusyTime() const {
    return {mStart.getTime(), mEnd};
}

CTime CEventRecurring::getEndTime() const {
    return mEnd;
}

size_t CEventRecurring::getEventDuration() const {
    return mEnd - mStart.getTime();
}

void CEventRecurring::setEnd(const CDatetime &end) {
    mEnd = end.getTime();
}

CEventRecurring::CEventRecurring(const CEventRecurring &eventRecurring): CEvent(eventRecurring) {
    mEnd = eventRecurring.mEnd;
}

CEventRecurring &CEventRecurring::operator=(CEventRecurring eventRecurring) {
    swapEvent(eventRecurring);
    swap(mEnd, eventRecurring.mEnd);

    return *this;
}
