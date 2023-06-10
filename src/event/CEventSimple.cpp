
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

bool CEventSimple::isConflict(const CEvent & event, int offset) const {
    CDatetime eventStart = event.getStart() + offset;
    CDatetime eventEnd = event.getEnd() + offset;

    if (event.isRecurring()) {
        if (event.happensOnDay(mStart.getYear(), mStart.getMonth(), mStart.getDay())) {
            if (eventStart.isInRange(mStart.getTime(), mEnd.getTime()) || eventEnd.isInRange(mStart.getTime(), mEnd.getTime())) {
                return true;
            }
        }
    }
    else {
        if (eventStart <= mEnd && eventEnd >= mStart ) {
            return true;
        }
    }

    return false;
}

CDatetime CEventSimple::getEnd() const {
    return mEnd;
}

bool CEventSimple::isRecurring() const {
    return false;
}

pair<CTime, CTime> CEventSimple::getForeverBusyTime() const {
    return {CTime(), CTime()};
}

CTime CEventSimple::getEndTime() const {
    return getEnd().getTime();
}

int CEventSimple::getEventDuration() const {
    return (int)abs(mEnd - mStart);
}

void CEventSimple::setEnd(const CDatetime &end) {
    mEnd = end;
}

bool CEventSimple::areEventDatesOk() const {
    if (!mStart.isValidDate() || !mEnd.isValidDate()) {
        return false;
    }

    return mStart < mEnd;
}

CEventSimple::CEventSimple(const CEventSimple &eventSimple): CEvent(eventSimple) {
    mEnd = eventSimple.mEnd;
}

CEventSimple &CEventSimple::operator=(CEventSimple eventSimple) {
    swapEvent(eventSimple);
    swap(mEnd, eventSimple.mEnd);

    return *this;
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

bool CEventSimple::happensOnDay(int year, int month, int day) const {
    auto date = CDatetime(year, month, day, 12, 0);
    auto startDate = CDatetime(mStart.getYear(), mStart.getMonth(), mStart.getDay(), 0, 0);
    auto endDate = CDatetime(mEnd.getYear(), mEnd.getMonth(), mEnd.getDay(), 23, 59);

    return date >= startDate && date <= endDate;
}

string &CEventSimple::exportEvent(string &fileRow) const {
    fileRow = to_string(mEventId) + ",sim," + mName + "," + mStart.toString() + "," + mEnd.toString() + "," + mPlace
            + "," + exportFormatVector(mAttendees) + "," + exportFormatVector(mTags) + "," + mNotes;
    return fileRow;
}
