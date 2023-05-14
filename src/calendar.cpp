#include "calendar.h"

static string failedMessage = "Adding of the event failed: ";

bool Calendar::addEvent(const Event &event) {
    for (auto const &[eventId, myEvent] : mEvents) {
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
