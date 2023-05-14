
#pragma once

#include "eventSimple.h"

class EventRecurring: public EventSimple {
public:
    EventRecurring(size_t eventId, const Datetime &start, const string &place, const vector<string> &attendees,
                   const set<string> &tags, const string &notes);

    [[nodiscard]] shared_ptr<Event> clone() const override;

    ostream &print(ostream &out) const override;

    /**
     * Figures out if the event
     *
     * @param event
     * @param offset
     * @return
     */
    [[nodiscard]] bool isConflict(const Event &event, size_t offset) const override;

};
