#include "CCalendar.h"
#include "CConflictSolver.h"


bool CCalendar::addEvent(CEvent &event, bool ignoreConflict) {
    size_t conflictEventId = getFirstConflictId(event);
    if (conflictEventId && ignoreConflict) {
        return false;
    }

    bool addSuccess = true;
    if (conflictEventId) {
        CConflictSolver conflictSolver(*this, conflictEventId);
        addSuccess = conflictSolver.solveAddConflict(event);
    }

    if (!addSuccess) {
        return false;
    }

    if (!ignoreConflict) {
        cout << "New event successfully added:";
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

map<size_t, shared_ptr<CEvent>> &CCalendar::getEvents() {
    return mEvents;
}

vector<shared_ptr<CEvent>> CCalendar::getSortedEvents(const shared_ptr<CEvent> &event, bool sortById) const {
    vector<shared_ptr<CEvent>> sortedEvents;

    for (const auto &[key, mEvent] : mEvents) {
        sortedEvents.push_back(mEvent);
    }

    if (event) {
        sortedEvents.push_back(event);
    }

    if (sortById) {
        sort(sortedEvents.begin(), sortedEvents.end(), CEvent::sortEventsById);
    }
    else {
        sort(sortedEvents.begin(), sortedEvents.end(), CEvent::sortEventsByStartDatetime);
    }

    return sortedEvents;
}

vector<shared_ptr<CEvent>> CCalendar::getDailyEvents(int year, int month, int day) const {
    vector<shared_ptr<CEvent>> sortedEvents;

    for (const auto &[key, mEvent] : mEvents) {
        if (mEvent->happensOnDay(year, month, day)) {
            sortedEvents.push_back(mEvent);
        }
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
            return eventId;
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
