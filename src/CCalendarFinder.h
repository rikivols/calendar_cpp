
#pragma once

#include "utils/CDatetime.h"
#include "CCalendar.h"
#include "importExport/CEventExporter.h"

#include <map>
#include <utility>

using namespace std;


class CCalendarFinder {
public:
    CCalendarFinder(CCalendar calendar, bool isAnd, string name, const CDatetime &start, const CDatetime &end, string mPlace,
                   const vector<string> &attendees, const vector<string> &tags);

    bool findEvents();

    void printEvents();

    void exportEvents();

private:
    void findByString(vector<shared_ptr<CEvent>> &events, const string &toMatch, int stringOption) const;

    void findByDate(vector<shared_ptr<CEvent>> &events, const CDatetime &date, bool isStart) const;

    void findByVector(vector<shared_ptr<CEvent>> &events, const vector<string> &vec, int vectorOption) const;

    void updateFinalEvents(vector<shared_ptr<CEvent>> &finalEvents,
                                                  const vector<shared_ptr<CEvent>> &tempEvents, bool &isFirst) const;

    string mName, mPlace, mNote;
    CDatetime mStart, mEnd;
    vector<string> mAttendees, mTags;
    bool mIsAnd;
    vector<shared_ptr<CEvent>> eventsResult;
    CCalendar mCalendar;
};


vector<shared_ptr<CEvent>> getIntersection(const vector<shared_ptr<CEvent>> &v1, const vector<shared_ptr<CEvent>> &v2);

vector<shared_ptr<CEvent>> getUnion(const vector<shared_ptr<CEvent>> &v1, const vector<shared_ptr<CEvent>> &v2);