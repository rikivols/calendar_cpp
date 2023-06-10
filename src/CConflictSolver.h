#pragma once

#include "CCalendar.h"

class CConflictSolver {
public:
    CConflictSolver(CCalendar calendar, size_t eventId);

    bool solveAddConflict(CEvent &event);

    int solveConflictPrompt();

private:
    static bool sortTimeByStart(const pair<CTime, CTime> &time1, const pair<CTime, CTime> &time2);

    static CTime findFreeTimeInRecurringEvents(vector<pair<CTime, CTime>> &foreverBusyVec, int durationMinutes,
                                               const CTime &start, const CTime &end);

    CDatetime getNextFreeDatetime(int durationMinutes, const CDatetime &from, size_t ignoreEventId=0,
                                  const shared_ptr<CEvent> &newFutureEvent=nullptr);

    CCalendar mCalendar;
    size_t mEventId;
};
