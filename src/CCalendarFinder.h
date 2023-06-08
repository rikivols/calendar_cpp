
#pragma once

#include "utils/CDatetime.h"
#include "CCalendar.h"

#include <map>
#include <utility>

using namespace std;


class CCalendarFinder {
public:
    CCalendarFinder(const CCalendar &calendar, bool isAnd, string name, const CDatetime &start, const CDatetime &end, string mPlace,
                   const vector<string> &attendees, const vector<string> &tags);

    bool findEvents();

    void printEvents();

    void exportEvents();

private:
    void findByString(map<size_t, shared_ptr<CEvent>> &events, const string &toMatch, int stringOption);

    void findByDate(map<size_t, shared_ptr<CEvent>> &events, const CDatetime &date, bool isStart);

    void findByVector(map<size_t, shared_ptr<CEvent>> &events, const vector<string> &vec, int vectorOption);

    void deepCopyEvents(map<size_t, shared_ptr<CEvent>> &finalEvents, const map<size_t, shared_ptr<CEvent>> &eventsToCopy);

    string mName, mPlace, mNote;
    CDatetime mStart, mEnd;
    vector<string> mAttendees, mTags;
    bool mIsAnd;
    map<size_t, shared_ptr<CEvent>> eventsResult;
    CCalendar mCalendar;

};