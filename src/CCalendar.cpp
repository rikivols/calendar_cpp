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

bool CCalendar::moveEvent(size_t eventId, int hours) {
    auto eventToMove = getEvent(eventId);
    size_t conflictEventId = getFirstConflictId(eventToMove, hours);
    if (conflictEventId) {
        cout << "An event already exists at that time, unable to move the event" << endl;
        cout << "Conflicting event:" << endl;
        cout << getEvent(conflictEventId);

        return false;
    }

    eventToMove->setStart(eventToMove->getStart() + hours);
    eventToMove->setEnd(eventToMove->getEnd() + hours);

    cout << "Event moved successfully, new event start: " << eventToMove->getStart() << endl;
    return true;
}

bool CCalendar::removeEvent(size_t eventId) {
    if (!getEvent(eventId)) {
        cout << "event doesn't exist" << endl;
        return false;
    }

    mEvents.erase(eventId);

    cout << "event with id: " << eventId << " removed successfully" << endl;

    return true;
}


shared_ptr<CEvent> CCalendar::getEvent(size_t eventId) {
    if (mEvents.find(eventId) != mEvents.end()) {
        return mEvents[eventId];
    }

    return nullptr;
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

size_t CCalendar::findNumberOfConflicts(const CEvent & event, int offset) const {

    size_t numOfConflicts = 0;

    for (auto const &[eventId, myEvent]: mEvents) {
        // polymorphism, we calculate differently if the conflict is recurring or a simple event
        if (event.getId() != eventId && myEvent->isConflict(event, offset)) {
            numOfConflicts++;
        }
    }

    return numOfConflicts;
}

size_t CCalendar::getFirstConflictId(const CEvent & event, int offset) const {

    for (auto const &[eventId, myEvent]: mEvents) {
        // polymorphism, we calculate differently if the conflict is recurring or a simple event
        if (event.getId() != eventId && myEvent->isConflict(event, offset)) {
            cout << failedMessage << "Event at that time already exists" << endl;
            cout << "The conflicted event:" << endl;
            cout << myEvent;
            return (int)eventId;
        }
    }

    return 0;
}

size_t CCalendar::findNumberOfConflicts(const shared_ptr<CEvent> & event, int offset) const {
    return getFirstConflictId((const CEvent &) event, offset);
}

size_t CCalendar::getFirstConflictId(const shared_ptr<CEvent> & event, int offset) const {
    return getFirstConflictId((const CEvent &) event, offset);;
}
