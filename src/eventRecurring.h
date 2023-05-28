
#pragma once

#include "eventSimple.h"

/**
 * Represents calendar's event that repeats every day. It has a start datetime, but it doesn't have the end.
 */
class EventRecurring: public Event {
public:
    EventRecurring(size_t eventId, string name, const Datetime &start, const Time &end, string place,
                   const vector<string> &attendees, const vector<string> &tags, string notes);

    [[nodiscard]] shared_ptr<Event> clone() const override;

    ostream &print(ostream &out) const override;

    /**
     * Finds out if calendar's event doesn't conflict with the provided event. Since recurring event repeats every
     * day and doesn't have the end, the calculation will be different.
     *
     * @param[in] event the event we want to check, whether it conflicts with the class's event
     * @param[in] offsetHours if we want to add or subtract hours of the provided event's datetime for searching of
     *                        the conflict, used for checking conflict when moving event
     * @return true = event conflicts, false = event doesn't conflict
     */
    [[nodiscard]] bool isConflict(const Event &event, int offsetHours) const override;
private:
    Time mEnd;
};
