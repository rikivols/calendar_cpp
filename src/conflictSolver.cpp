//
// Created by Anon user on 28.05.2023.
//
#include "conflictSolver.h"

#include <utility>

ConflictSolver::ConflictSolver(Calendar calendar, size_t eventId): mCalendar(std::move(calendar)), mEventId(eventId) {}

int ConflictSolver::solveConflict() {
    return 0;
}

