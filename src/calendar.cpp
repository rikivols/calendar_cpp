#include "calendar.h"

static string failedMessage = "Adding of the event failed: ";

bool Calendar::addEvent(const Event &event) {
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

shared_ptr<Event> Calendar::getEvent(size_t eventId) {
    if (mEvents.find(eventId) != mEvents.end()) {
        return mEvents[eventId];
    }

    throw logic_error("Event not found");
}
