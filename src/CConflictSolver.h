#pragma once

#include "CCalendar.h"

class CConflictSolver {
public:
    /**
     * Initialize the calendar for the conflict solver and event id of the conflicted event.
     *
     * @param calendar the calendar we want to solve conflict in
     * @param eventId eventId of the underlying, conflicted event
     */
    CConflictSolver(CCalendar calendar, size_t eventId);

    /**
     * Solves conflict that results in the add operation, prompts user to select how he wants to solve it.
     *
     * @param event new event to be added
     * @return true = conflict resolved, false = conflict wasn't resolved
     */
    bool solveAddConflict(CEvent &event);

    /**
     * Prompts user how he wants to solve the conflict
     *
     * @return option of what the user decided to be the solution to the conflict
     */
    int solveConflictPrompt();

    /**
     * Gets the next available datetime to change our value to. Can give false positives to the new recurring events,
     * it can be free at that time but busy later in the future. Need to check for that option after using the function.
     *
     * @param durationMinutes how long our event is that we want to have a free spot for
     * @param from start of the event that we want to have a free spot for
     * @param ignoreEventId if we want to ignore a certain event id when searching for the new event
     * @param newFutureEvent a new event that we want to temporarily add to the calendar while searching
     * @return next free datetime for the event
     */
    CDatetime getNextFreeDatetime(int durationMinutes, const CDatetime &from, size_t ignoreEventId=0,
                                  const shared_ptr<CEvent> &newFutureEvent=nullptr);

private:
    static bool sortTimeByStart(const pair<CTime, CTime> &time1, const pair<CTime, CTime> &time2);

    /**
     * Finds next free time in the recurring events.
     *
     * @param foreverBusyVec recurring events that we are finding free time in
     * @param durationMinutes duration of the event that we want to find free time of
     * @param start start of the event that we want to find free time of
     * @param end end of the event that we want to find free time of
     * @return next free time for the event, invalid time if we couldn't find one
     */
    static CTime findFreeTimeInRecurringEvents(vector<pair<CTime, CTime>> &foreverBusyVec, int durationMinutes,
                                               const CTime &start, const CTime &end);

    CCalendar mCalendar;
    size_t mEventId;
};
