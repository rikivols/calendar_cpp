//
// Created by Anon user on 28.05.2023.
//
#include "CConflictSolver.h"
#include "CHelpers.cpp"
#include <utility>

CConflictSolver::CConflictSolver(CCalendar calendar, size_t eventId): mCalendar(std::move(calendar)), mEventId(eventId) {}

bool CConflictSolver::solveAddConflict(CEvent &event) {
    int userOption = solveConflictPrompt();
    CDatetime eventStart;


    switch (userOption) {
        case 1:
            eventStart = getNextFreeDatetime(event.getEventDuration(), event.getStart());
            if (!eventStart.isValidDate()) {
                cout << "Different time for the new event couldn't be found" << endl;
                return false;
            }
            break;
        case 2:
            size_t numOfConflicts = mCalendar.findNumberOfConflicts(event);
            if (numOfConflicts > 1) {
                cout << "Multiple events conflict with your new event, can't move them" << endl;
                return false;
            }
            auto conflictedEvent = mCalendar.getEvent(mEventId);

            // we check if it would be possible to move the item (if we were to insert it)
            eventStart = getNextFreeDatetime(conflictedEvent->getEventDuration(),
                                             event.getStart() + event.getEventDuration() + 1, conflictedEvent->getId(),
                                             event.clone());
            if (!eventStart.isValidDate()) {
                cout << "Different time for the new event couldn't be found" << endl;
                return false;
            }

            

            break;
        case 3:
            cout << "Aborting the adding of an event." << endl;
            break;
        default:
            throw logic_error("User option out of range");
    }

    cout << "New date found for the event, its start date will be: " << eventStart << endl;
    event.setStart(eventStart);
    event.setEnd(eventStart + event.getEventDuration());

    return true;
}

int CConflictSolver::solveConflictPrompt() {
    cout << "Conflict detected: event already exists at that time." << endl;
    cout << "The conflicted event:" << endl;
    cout << mCalendar.getEvent(mEventId);

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
CTime CConflictSolver::findFreeTimeInRecurringEvents(vector<pair<CTime, CTime>> &foreverBusyVec, size_t durationMinutes,
                                       const CTime &start, const CTime &end) {
    sort(foreverBusyVec.begin(), foreverBusyVec.end(), sortTimeByStart);
    CTime result = start;
    CTime resultEnd = result + durationMinutes;

    for (const auto &busyRange: foreverBusyVec) {
        if (!result.isInRange(busyRange.first, busyRange.second) && !resultEnd.isInRange(busyRange.first, busyRange.second)
            && result.isInRange(start, end) && resultEnd.isInRange(start, end)) {
            return result;
        }

        result = busyRange.second + 1;
        resultEnd = result + durationMinutes;
    }

    if (result.isInRange(start, end) && resultEnd.isInRange(start, end)) {
        return result;
    }

    return {};
}

CDatetime CConflictSolver::getNextFreeDatetime(size_t durationMinutes, const CDatetime &from, size_t ignoreEventId,
                                               const shared_ptr<CEvent> &newFutureEvent) {
    auto sortedEvents = mCalendar.getSortedEvents();

    vector<pair<CTime, CTime>> foreverBusyVec;
    pair<CTime, CTime> foreverBusyRange;
    CDatetime result = from;
    CDatetime resultEnd = result + durationMinutes;
    CTime tempResult;

    for (const auto &event: sortedEvents) {
        if (event->getId() == ignoreEventId) {
            continue;
        }

        // if time even fits
        if (resultEnd > event->getStart()) {
            tempResult = findFreeTimeInRecurringEvents(foreverBusyVec, durationMinutes, result, resultEnd);
            // we have found the time
            if (tempResult.isValidTime()) {
                result.setTime(tempResult);
                return result;
            }
        }

        foreverBusyRange = event->getForeverBusyTime();

        if (foreverBusyRange.first.isValidTime() && foreverBusyRange.second.isValidTime()) {
            foreverBusyVec.push_back(foreverBusyRange);
            result.setTime(foreverBusyRange.second);
        }
        else {
            result = event->getEnd() + 1;  // next free minute
        }
    }

    tempResult = findFreeTimeInRecurringEvents(foreverBusyVec, durationMinutes, result, resultEnd);
    if (tempResult.isValidTime()) {
        result.setTime(tempResult);
        return result;
    }
    return {};  // it was impossible to find a free time
}
