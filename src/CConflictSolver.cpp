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

