
#pragma once

#include <map>
#include <set>

#include "event.h"


/**
 * Represents the calendar and what actions can be done on the events.
 */
class Calendar {
public:
    explicit Calendar();

    /**
     * Adds event to the calendar if possible. Implementation of the event->isConflict polymorphism
     *
     * @param[in] event
     * @return true = adding was successful
     *         false = adding wasn't successful, display why it failed
     */
    bool addEvent(const Event &event);

    shared_ptr<Event> getEvent(size_t eventId);

    /**
     * Adds event to the calendar if possible. Implementation of the event->isConflict polymorphism
     *
     * @param[in] eventId id of an event we want to move
     * @param[in] hours by how many hours we want to move our event, we support negative values too
     * @return true = moving was successful
     *         false = moving wasn't successful, display why it failed
     */
    bool moveEvent(size_t eventId, int hours);

    /**
     * Removes the event with the given id
     *
     * @param[in] eventId id of the event we want to remove
     * @return true = deleting was successful
     *         false = event with the given id doesn't exist
     */
    bool removeEvent(size_t eventId);

    /**
     * Find events based on the given criteria. We can also choose if we want to use AND or OR separators
     *
     * @param[in] rangeStart Event that happened after the datetime
     * @param[in] rangeEnd Event that happened before the datetime
     * @param[in] place place where the event is happening
     * @param[in] attendees people that attend the event
     * @param[in] tags tags of the event
     * @param[in] isAnd true for using AND search separator, false for using OR separator
     * @return map of the found events based on the criteria. This format makes it easier to export.
     */
    const map<size_t, shared_ptr<Event>> &findEvents(const Datetime &rangeStart, const Datetime &rangeEnd,
                                                     const string &place, const vector<string> &attendees,
                                                     const set<string> &tags, bool isAnd);

protected:
    map<size_t, shared_ptr<Event>> mEvents;
};
