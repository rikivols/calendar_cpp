
#pragma once

#include <set>
#include <string>
#include <vector>

#include "event.h"

/**
 * Represents calendar's event that doesn't repeat.
 */
class EventSimple: public Event {
public:
    EventSimple(size_t eventId, string name, const Datetime &start, const Datetime &end, string place, const vector<string> &attendees,
                const set<string> &tags, const string &notes);

    [[nodiscard]] shared_ptr<Event> clone() const override;

    ostream &print(ostream &out) const override;

    /**
     * Replaces the current start of the event by the provided datetime.
     *
     * @param[in] datetime Datetime we want to have at start
     */
    void setStart(const Datetime & datetime) override;

    /**
     * Replaces the current end of the event by the provided datetime.
     *
     * @param[in] datetime Datetime we want to have at end
     */
    void setEnd(const Datetime & datetime) override;

    /**
     * @return event id
     */
    [[nodiscard]] size_t getId() const override;

    /**
     * Finds out if calendar's event doesn't conflict with the provided event.
     *
     * @param[in] event the event we want to check, whether it conflicts with the class's event
     * @param[in] offsetHours if we want to add or subtract hours of the provided event's datetime for searching of
     *                        the conflict, used for checking conflict when moving event
     * @return true = event conflicts, false = event doesn't conflict
     */
    [[nodiscard]] bool isConflict(const Event &event, int offsetHours) const override;

protected:
    size_t mEventId;
    string mName;
    Datetime mStart;
    Datetime mEnd;
    string mPlace;
    vector<string> mAttendees;
    set<string> mTags;
    string mNotes;
};
