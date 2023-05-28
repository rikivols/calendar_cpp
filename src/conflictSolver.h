#include "event.h"
#include "calendar.h"

class ConflictSolver {
public:
    ConflictSolver(Calendar calendar, size_t eventId);

    int solveConflict();

private:
    Calendar mCalendar;
    size_t mEventId;
};
