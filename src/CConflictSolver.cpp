//
// Created by Anon user on 28.05.2023.
//
#include "CConflictSolver.h"
#include "CHelpers.cpp"
#include <utility>

CConflictSolver::CConflictSolver(CCalendar calendar, size_t eventId): mCalendar(std::move(calendar)), mEventId(eventId) {}

int CConflictSolver::solveConflict() {
    cout << "Conflict detected: event already exists at that time." << endl;
    cout << "The conflicted event:" << endl;
    cout << mCalendar.getEvent(mEventId);

    cout << "How do you want to handle this situation?" << endl;
    cout << "1 - Move the new event to the closest time in the future" << endl;
    cout << "2 - Move the conflicted event (with id: " << mEventId << ") to the closest time in the future" << endl;
    cout << "3 - Abort" << endl;

    int option = getUserOption(3);

    switch (option) {
//        case 1:
    }

    return 1;
}

