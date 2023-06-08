
#include "CCalendarFinder.h"


CCalendarFinder::CCalendarFinder(const CCalendar &calendar, bool isAnd, string name, const CDatetime &start, const CDatetime &end,
                               string place, const vector<string> &attendees, const vector<string> &tags
                               ): mCalendar(calendar), mIsAnd(isAnd), mName(std::move(name)), mStart(start), mEnd(end), mPlace(std::move(place)),
                                  mAttendees(attendees), mTags(tags) {}


bool CCalendarFinder::findEvents() {
    map<size_t, shared_ptr<CEvent>> finalEvents, tempEvents;
    bool isFirst = true;

    if (!mName.empty()) {
        findByString(tempEvents, mName, 1);
        deepCopyEvents(tempEvents, finalEvents);
    }
    if (mStart.isValidDate()) {

    }

}


void CCalendarFinder::findByString(map<size_t, shared_ptr<CEvent>> &events, const string &toMatch, int stringOption) {

}

void CCalendarFinder::findByDate(map<size_t, shared_ptr<CEvent>> &events, const CDatetime &date, bool isStart) {

}

