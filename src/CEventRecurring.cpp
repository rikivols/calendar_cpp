
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

bool CEventRecurring::isConflict(const CEvent &event, int offsetHours) const {
    return false;
}

ostream &CEventRecurring::print(ostream &out) const {
    return out;
}

pair<CTime, CTime> CEventRecurring::getUnavailableTime() const {
    return {mStart.getTime(), mEnd};
}
