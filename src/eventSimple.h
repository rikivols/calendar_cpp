
#pragma once

#include <set>
#include <string>
#include <vector>

#include "event.h"

class EventSimple: public Event {
public:
    EventSimple(size_t eventId, const Datetime &start, const Datetime &end, string place, const vector<string> &attendees,
                const set<string> &tags, const string &notes);

    [[nodiscard]] shared_ptr<Event> clone() const override;

    ostream &print(ostream &out) const override;

    void setStart(const Datetime & datetime) override;

    /**
     * Year, month, day will be 0 if it's recurring.
     * @param datetime
     */
    void setEnd(const Datetime & datetime) override;

    [[nodiscard]] size_t getId() const override;

    [[nodiscard]] bool isConflict(const Event &event, size_t offset) const override;

protected:
    size_t mEventId;
    Datetime mStart;
    Datetime mEnd;
    string mPlace;
    vector<string> mAttendees;
    set<string> mTags;
    string mNotes;
};
