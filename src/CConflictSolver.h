#include "CEvent.h"
#include "CCalendar.h"

class CConflictSolver {
public:
    CConflictSolver(CCalendar calendar, size_t eventId);

    bool solveAddConflict(CEvent &event);

    int solveConflictPrompt();

    static bool sortTimeByStart(const pair<CTime, CTime> &time1, const pair<CTime, CTime> &time2);

    CDatetime getNextFreeDatetime(size_t durationMinutes, const CDatetime &from, size_t ignoreEventId=0, const shared_ptr<CEvent> &newFutureEvent=nullptr);

    static CTime findFreeTimeInRecurringEvents(vector<pair<CTime, CTime>> &foreverBusyVec, size_t durationMinutes, const CTime &start, const CTime &end) ;

private:
    CCalendar mCalendar;
    size_t mEventId;
};
