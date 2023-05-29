#include "CCalendar.h"

static string failedMessage = "Adding of the event failed: ";

bool CCalendar::addEvent(const CEvent &event) {
    for (auto const &[eventId, myEvent]: mEvents) {
        // polymorphism, we calculate differently if the conflict is recurring or a simple event
        if (myEvent->isConflict(event, 0)) {
            cout << failedMessage << "Event at that time already exists" << endl;
            cout << "The conflicted event:" << endl;
            cout << myEvent;
            return false;
        }
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

bool CCalendar::sortEventsByStartDatetime(const shared_ptr<CEvent>& event1, const shared_ptr<CEvent>& event2) {
    return event1->getStart() < event2->getStart();
}


vector<shared_ptr<CEvent>> CCalendar::getSortedEvents() const {
    vector<shared_ptr<CEvent>> sortedEvents;

    for (const auto &[key, mEvent] : mEvents) {
        sortedEvents.push_back(mEvent);
    }

    sort(sortedEvents.begin(), sortedEvents.end(), sortEventsByStartDatetime);

    return sortedEvents;
}
