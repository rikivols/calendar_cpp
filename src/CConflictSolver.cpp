//
// Created by Anon user on 28.05.2023.
//
#include "CConflictSolver.h"
#include <utility>

CConflictSolver::CConflictSolver(CCalendar calendar, size_t eventId): mCalendar(std::move(calendar)), mEventId(eventId) {}

bool CConflictSolver::solveAddConflict(CEvent &newEvent) {
    int userOption = solveConflictPrompt();
    CDatetime newEventStart;


    switch (userOption) {
        case 1: {
            newEventStart = getNextFreeDatetime(newEvent.getEventDuration(), newEvent.getStart());
            if (!newEventStart.isValidDate()) {
                cout << "Different time for the new event couldn't be found" << endl;
                return false;
            }

            cout << "New date found for the event, its start date will be: " << newEventStart << endl;
            newEvent.setStart(newEventStart);
            newEvent.setEnd(newEventStart + (int)newEvent.getEventDuration());

            break;
        }
        case 2: {
            size_t numOfConflicts = mCalendar.findNumberOfConflicts(newEvent);
            if (numOfConflicts > 1) {
                cout << "Multiple events conflict with your new event, can't move them" << endl;
                return false;
            }
            auto conflictedEvent = mCalendar.getEvent(mEventId);
            int conflictedEventDuration = conflictedEvent->getEventDuration();
            CDatetime oldStart = conflictedEvent->getStart();
            CDatetime oldEnd = conflictedEvent->getEnd();

            // we check if it would be possible to move the item (if we were to insert it)
            newEventStart = getNextFreeDatetime(conflictedEventDuration, newEvent.getStart() + newEvent.getEventDuration() + 1,
                                             conflictedEvent->getId(), newEvent.clone());
            if (!newEventStart.isValidDate()) {
                cout << "We couldn't find a spot to move the new event to, aborting." << endl;
                return false;
            }

            // now we check if it is possible to insert the new event after it's been moved
            conflictedEvent->setStart(newEventStart);
            conflictedEvent->setEnd(newEventStart + conflictedEventDuration);

            // if there's a conflict after we just moved the underlying event, we can't perform this action
            if (mCalendar.getFirstConflictId(newEvent)) {
                cout << "We couldn't insert the new event after moving, aborting." << endl;
                conflictedEvent->setStart(oldStart);
                conflictedEvent->setEnd(oldEnd);

                return false;
            }
            else {
                cout << "Event moved successfully, new date for it: " << newEventStart << endl;
            }
        }
            break;
        case 3: {
            cout << "Aborting the adding of an event." << endl;

            return false;
        }
        default:
            throw logic_error("User option out of range");
    }

    return true;
}

int CConflictSolver::solveConflictPrompt() {
    cout << endl << "CONFLICT DETECTED: event already exists at that time." << endl;
    cout << "Newly added event conflicts with the following event:";
    cout << *mCalendar.getEvent(mEventId) << endl;

    cout << "How do you want to handle this situation?" << endl;
    cout << "1 - Move the new event to the closest time in the future" << endl;
    cout << "2 - Move the conflicted event (with id: " << mEventId << ") to the closest time in the future" << endl;
    cout << "3 - Abort" << endl;

    return getUserOption(3);

}

bool CConflictSolver::sortTimeByStart(const pair<CTime, CTime> &time1, const pair<CTime, CTime> &time2) {
    return time1.second < time2.second;
}

// we include start
CTime CConflictSolver::findFreeTimeInRecurringEvents(vector<pair<CTime, CTime>> &foreverBusyVec, int durationMinutes,
                                       const CTime &start, const CTime &end) {
    sort(foreverBusyVec.begin(), foreverBusyVec.end(), sortTimeByStart);
    CTime result = start;
    CTime resultEnd = end;

    for (const auto &busyRange: foreverBusyVec) {
        if (!result.isInRange(busyRange.first, busyRange.second) && !resultEnd.isInRange(busyRange.first, busyRange.second)) {
//            && result.isInRange(start, end) && resultEnd.isInRange(start, end)) {
            return result;
        }

        result = busyRange.second.addMinutes(1);
        resultEnd = result.addMinutes(durationMinutes);
    }

//    if (result.isInRange(start, end) && resultEnd.isInRange(start, end)) {
    // if the result is still not valid event after it was moved so many times, we are not able to find any free date
    for (const auto &busyRange: foreverBusyVec) {
        if (!result.isInRange(busyRange.first, busyRange.second) && !resultEnd.isInRange(busyRange.first, busyRange.second)) {
            return result;
        }
    }
//    }

    return {};
}

CDatetime CConflictSolver::getNextFreeDatetime(int durationMinutes, const CDatetime &from, size_t ignoreEventId,
                                               const shared_ptr<CEvent> &newFutureEvent) {
    auto sortedEvents = mCalendar.getSortedEvents(newFutureEvent);

    vector<pair<CTime, CTime>> foreverBusyVec;
    pair<CTime, CTime> foreverBusyRange;
    CDatetime result = from;
    CDatetime resultEnd = result + durationMinutes;
    CTime tempResult;

    for (const auto &event: sortedEvents) {
        if (event->getId() == ignoreEventId) {
            continue;
        }

        // if the next event in the sorted order is already occupying that time, we won't be able to insert it
        // that's why we can just go to the next time slot
        if (resultEnd < event->getStart()) {
            tempResult = findFreeTimeInRecurringEvents(foreverBusyVec, durationMinutes, result, resultEnd);
            // we check if we found next time slot in the recurring daily events and also if the new time slot
            // isn't too far in the future
            if (tempResult.isValidTime() && tempResult < event->getStart()) {
                result.setTime(tempResult);
                return result;
            }
        }

        foreverBusyRange = event->getForeverBusyTime();

        // the event is recurring, and we'll add it to the recurring events vector
        if (foreverBusyRange.first.isValidTime() && foreverBusyRange.second.isValidTime()) {
            foreverBusyVec.push_back(foreverBusyRange);
            result.setTime(foreverBusyRange.second);
            resultEnd.setTime(result + durationMinutes);
        }
        else {
            result = event->getEnd() + 1;  // next free minute
            resultEnd = result + durationMinutes;
        }
    }

    // last check, if we're able to find any time in the future amongst daily recurring events
    tempResult = findFreeTimeInRecurringEvents(foreverBusyVec, durationMinutes, result, resultEnd);
    if (tempResult.isValidTime()) {
        result.setTime(tempResult);
        return result;
    }

    // it was impossible to find a free time, every date in the future is already taken by the recurring events
    return {};
}
