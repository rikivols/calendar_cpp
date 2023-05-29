#include "CEvent.h"
#include "CCalendar.h"

class CConflictSolver {
public:
    CConflictSolver(CCalendar calendar, size_t eventId);

    int solveAddConflict(const CEvent &event);

    int solveConflictPrompt();

private:
    CCalendar mCalendar;
    size_t mEventId;
};
