
#pragma once

#include <map>
#include <set>

#include "event/CEvent.h"


/**
 * Represents the calendar and what actions can be done on the events.
 */
class CCalendar {
public:
    explicit CCalendar() = default;

    /**
     * Adds event to the calendar if possible. Solves conflicts if not.
     *
     * @param event event to add
     * @param ignoreConflict whether to ignore the conflict and return false in that case and not print the event
     * @return true = adding was successful
     *         false = adding wasn't successful
     */
    bool addEvent(CEvent &event, bool ignoreConflict=false);

    /**
     * Moves event if possible by given amount of hours.
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
     * Gets event by id.
     *
     * @param eventId event id to get.
     * @return Shared pointer to the event or nullptr if not found.
     */
    shared_ptr<CEvent> getEvent(size_t eventId);

    /**
     * Returns sorted events by a start datetime or event id.
     *
     * @param events optional new event we can add to the sorted events
     * @param sortById true = sort by id, false = sort by start datetime
     * @return sorted events as a vector
     */
    [[nodiscard]] vector<shared_ptr<CEvent>> getSortedEvents(const shared_ptr<CEvent> &event, bool sortById) const;

    /**
     * Gets events happening on that day sorted by the start datetime.
     *
     * @param year year of the date
     * @param month month of the date
     * @param day day of the date
     * @return vector of sorted events happening on that day
     */
    [[nodiscard]] vector<shared_ptr<CEvent>> getDailyEvents(int year, int month, int day) const;

    /**
     * Returns a first id of an event that our event is conflicting with.
     *
     * @param event event to check conflict for
     * @param offset how many hours to add to the event to check the conflict
     * @return id of an event that our event conflicts with or 0 is none
     */
    [[nodiscard]] size_t getFirstConflictId(const CEvent &event, int offset=0) const;

    /**
     * Returns a number of conflicts our event has.
     *
     * @param event event to check conflict for
     * @param offset how many hours to add to the event to check the conflict
     * @return number of conflicts for our event
     */
    [[nodiscard]] size_t findNumberOfConflicts(const CEvent &event, int offset=0) const;

    /**
     * Returns a first id of an event that our event is conflicting with.
     *
     * @param event event to check conflict for
     * @param offset how many hours to add to the event to check the conflict
     * @return id of an event that our event conflicts with or 0 is none
     */
    [[nodiscard]] size_t getFirstConflictId(const shared_ptr<CEvent> &event, int offset) const;

private:
    // using shared ptr because I'm using these events in the conflict solver and calendar exporter
    map<size_t, shared_ptr<CEvent>> mEvents;
};
