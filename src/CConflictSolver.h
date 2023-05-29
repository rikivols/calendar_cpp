#include "CEvent.h"
#include "CCalendar.h"

class CConflictSolver {
public:
    CConflictSolver(CCalendar calendar, size_t eventId);

    int solveAddConflict(const CEvent &event);

    int solveConflictPrompt();

    static bool sortTimeByStart(const pair<CTime, CTime> &time1, const pair<CTime, CTime> &time2);

    CDatetime getNextFreeDatetime(const vector<shared_ptr<CEvent>> &sortedEvents, int durationMinutes, const CDatetime &from);

    CTime findFreeTimeInRecurringEvents(vector<pair<CTime, CTime>> &foreverBusyVec, int durationMinutes, const CTime &start, const CTime &end) const;

private:
    CCalendar mCalendar;
    size_t mEventId;
};
