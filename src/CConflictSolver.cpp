//
// Created by Anon user on 28.05.2023.
//
#include "CConflictSolver.h"
#include "CHelpers.cpp"
#include <utility>

CConflictSolver::CConflictSolver(CCalendar calendar, size_t eventId): mCalendar(std::move(calendar)), mEventId(eventId) {}

int CConflictSolver::solveAddConflict(const CEvent &event) {
    int userOption = solveConflictPrompt();

    switch (userOption) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            cout << "Aborting the adding of an event." << endl;
            break;
    }
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
CTime CConflictSolver::findFreeTimeInRecurringEvents(vector<pair<CTime, CTime>> &foreverBusyVec, int durationMinutes,
                                       const CTime &start, const CTime &end) const {
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

CDatetime CConflictSolver::getNextFreeDatetime(const vector<shared_ptr<CEvent>> &sortedEvents, int durationMinutes,
                                               const CDatetime &from) {
    vector<pair<CTime, CTime>> foreverBusyVec;
    pair<CTime, CTime> foreverBusyRange;
    CDatetime result = from;
    CDatetime resultEnd = result + durationMinutes;
    CTime tempResult;

    for (const auto &event: sortedEvents) {
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

