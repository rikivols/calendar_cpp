
#include "CEventSimple.h"

#include <utility>


CEventSimple::CEventSimple(size_t eventId, string name, const CDatetime &start, const CDatetime &end, string place,
                           const vector<string> &attendees, const vector<string> &tags,
                           string notes) : CEvent(eventId, std::move(name), start, std::move(place), attendees, tags,
                                                  std::move(notes)) {
    mEnd = end;
}


CEventSimple::CEventSimple(const CEventSimple &eventSimple) : CEvent(eventSimple) {
    mEnd = eventSimple.mEnd;
}


CEventSimple::CEventSimple(CEventSimple &&eventSimple) noexcept: CEvent(std::move(eventSimple)),
                                                                 mEnd(std::move(eventSimple.mEnd)) {}


CEventSimple &CEventSimple::operator=(CEventSimple eventSimple) {
    swapEvent(eventSimple);
    swap(mEnd, eventSimple.mEnd);

    return *this;
}


shared_ptr<CEvent> CEventSimple::clone() const {
    return std::make_shared<CEventSimple>(*this);
}


ostream &CEventSimple::print(ostream &out) const {
    printSeparator(out);
    out << "| Simple event" << endl;
    out << "| Id: " << mEventId << endl;
    out << "| Start Date: " << mStart << endl;
    out << "| End Date: " << mEnd << endl;
    partialPrint(out);

    return out;
}


CDatetime CEventSimple::getEnd() const {
    return mEnd;
}


int CEventSimple::getEventDuration() const {
    return (int) abs(mEnd - mStart);
}


bool CEventSimple::areEventDatesOk() const {
    if (!mStart.isValidDate() || !mEnd.isValidDate()) {
        return false;
    }

    return mStart < mEnd;
}


bool CEventSimple::happensOnDay(int year, int month, int day) const {
    auto date = CDatetime(year, month, day, 12, 0);
    auto startDate = CDatetime(mStart.getYear(), mStart.getMonth(), mStart.getDay(), 0, 0);
    auto endDate = CDatetime(mEnd.getYear(), mEnd.getMonth(), mEnd.getDay(), 23, 59);

    return date >= startDate && date <= endDate;
}


pair<CTime, CTime> CEventSimple::getForeverBusyTime() const {
    return {CTime(), CTime()};
}


void CEventSimple::setEnd(const CDatetime &end) {
    mEnd = end;
}


bool CEventSimple::isRecurring() const {
    return false;
}


bool CEventSimple::isConflict(const CEvent &event, int offset) const {
    CDatetime eventStart = event.getStart() + offset * 60;
    CDatetime eventEnd = event.getEnd() + offset * 60;

    if (event.isRecurring()) {
        if (event.happensOnDay(mStart.getYear(), mStart.getMonth(), mStart.getDay())) {
            if (eventStart.isInRange(mStart.getTime(), mEnd.getTime()) ||
                eventEnd.isInRange(mStart.getTime(), mEnd.getTime())) {
                return true;
            }
        }
    } else {
        if (eventStart <= mEnd && eventEnd >= mStart) {
            return true;
        }
    }

    return false;
}


string &CEventSimple::exportEvent(string &fileRow) const {
    fileRow = to_string(mEventId) + ",sim," + mName + "," + mStart.toString() + "," + mEnd.toString() + "," + mPlace
              + "," + exportFormatVector(mAttendees) + "," + exportFormatVector(mTags) + "," + mNotes;
    return fileRow;
}
