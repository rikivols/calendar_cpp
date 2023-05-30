#pragma once

#include "CCalendar.h"
#include "CConflictSolver.h"

static string failedMessage = "Adding of the event failed: ";

bool CCalendar::addEvent(CEvent &event) {
    size_t conflictEventId = getFirstConflictId(event);
    bool addSuccess = true;
    if (conflictEventId) {
        CConflictSolver conflictSolver(*this, conflictEventId);
        addSuccess = conflictSolver.solveAddConflict(event);
    }

    if (addSuccess) {
        cout << "New event successfully added:" << endl;
        cout << event;
    }

    mEvents[event.getId()] = event.clone();

    return true;
}

shared_ptr<CEvent> CCalendar::getEvent(size_t eventId) {
    if (mEvents.find(eventId) != mEvents.end()) {
        return mEvents[eventId];
    }

    throw logic_error("Event not found");
}

vector<shared_ptr<CEvent>> CCalendar::getSortedEvents(const shared_ptr<CEvent> &event) const {
    vector<shared_ptr<CEvent>> sortedEvents;

    for (const auto &[key, mEvent] : mEvents) {
        sortedEvents.push_back(mEvent);
    }

    if (event) {
        sortedEvents.push_back(event);
    }

    sort(sortedEvents.begin(), sortedEvents.end(), CEvent::sortEventsByStartDatetime);

    return sortedEvents;
}

size_t CCalendar::findNumberOfConflicts(const CEvent & event) const {

    size_t numOfConflicts = 0;

    for (auto const &[eventId, myEvent]: mEvents) {
        // polymorphism, we calculate differently if the conflict is recurring or a simple event
        if (event.getId() != eventId && myEvent->isConflict(event, 0)) {
            numOfConflicts++;
        }
    }

    return numOfConflicts;
}

size_t CCalendar::getFirstConflictId(const CEvent & event) const {

    for (auto const &[eventId, myEvent]: mEvents) {
        // polymorphism, we calculate differently if the conflict is recurring or a simple event
        if (event.getId() != eventId && myEvent->isConflict(event, 0)) {
            cout << failedMessage << "Event at that time already exists" << endl;
            cout << "The conflicted event:" << endl;
            cout << myEvent;
            return (int)eventId;
        }
    }

    return 0;
}


