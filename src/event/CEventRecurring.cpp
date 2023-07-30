
#include "CEventRecurring.h"


CEventRecurring::CEventRecurring(size_t eventId, string name, const CDatetime &start, const CTime &end, string place,
                                 const vector<string> &attendees, const vector<string> &tags,
                                 string notes) : CEvent(eventId, std::move(name), start, std::move(place), attendees,
                                                        tags, std::move(notes)) {
    mEnd = end;
}


CEventRecurring::CEventRecurring(const CEventRecurring &eventRecurring) : CEvent(eventRecurring) {
    mEnd = eventRecurring.mEnd;
}


CEventRecurring::CEventRecurring(CEventRecurring &&eventRecurring) noexcept: CEvent(std::move(eventRecurring)),
                                                                             mEnd(eventRecurring.mEnd) {}


CEventRecurring &CEventRecurring::operator=(CEventRecurring eventRecurring) {
    swapEvent(eventRecurring);
    swap(mEnd, eventRecurring.mEnd);

    return *this;
}


shared_ptr<CEvent> CEventRecurring::clone() const {
    return std::make_shared<CEventRecurring>(*this);
}


ostream &CEventRecurring::print(ostream &out) const {
    printSeparator(out);
    out << "| Recurring event (repeats daily)" << endl;
    out << "| Id: " << mEventId << endl;
    out << "| Start Date: " << mStart << endl;
    out << "| Repeating interval: " << mStart.getTime() << " - " << mEnd << endl;
    partialPrint(out);

    return out;
}


CDatetime CEventRecurring::getEnd() const {
    return {2110, 1, 1, mEnd.getHour(), mEnd.getMinute()};
}


int CEventRecurring::getEventDuration() const {
    return abs(mEnd - mStart.getTime());
}


bool CEventRecurring::areEventDatesOk() const {
    if (!mStart.isValidDate() || !mEnd.isValidTime()) {
        return false;
    }

    return mStart.getTime() != mEnd;
}


bool CEventRecurring::happensOnDay(int year, int month, int day) const {
    return mStart <= CDatetime(year, month, day, 23, 59);
}


pair<CTime, CTime> CEventRecurring::getForeverBusyTime() const {
    return {mStart.getTime(), mEnd};
}


void CEventRecurring::setEnd(const CDatetime &end) {
    mEnd = end.getTime();
}


bool CEventRecurring::isRecurring() const {
    return true;
}


bool CEventRecurring::isConflict(const CEvent &event, int offset) const {
    CDatetime eventStart = event.getStart() + (offset * 60);
    CDatetime eventEnd = event.getEnd() + (offset * 60);
    if (mStart - event.getEventDuration() <= eventStart) {
        if (eventStart.isInRange(mStart.getTime(), mEnd) || eventEnd.isInRange(mStart.getTime(), mEnd) ||
            event.getEventDuration() >= DAY_MINUTES) {
            return true;
        }
    }

    return false;
}


string &CEventRecurring::exportEvent(string &fileRow) const {
    fileRow = to_string(mEventId) + ",rec," + mName + "," + mStart.toString() + "," + mEnd.toStringTime() + "," + mPlace
              + "," + exportFormatVector(mAttendees) + "," + exportFormatVector(mTags) + "," + mNotes;
    return fileRow;
}
