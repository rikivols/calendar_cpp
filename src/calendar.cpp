#include "calendar.h"

Calendar::Calendar(bool isImport, const string &importFilePath) {}

bool Calendar::addEvent(const shared_ptr<Event> &event) {
    for (auto const &[eventId, myEvent] : mEvents) {
        if (myEvent->isConflict(event, 0)) {
            return false;
        }
    }

    mEvents[event->getId()] = event;

    return true;
}
