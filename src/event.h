
#pragma once

#include <iostream>

#include "datetime.h"

/**
 * Abstract class of the calendar's event.
 */
class Event {
public:
    Event(size_t eventId, string name, const Datetime &start, string place,
          const vector<string> &attendees, const vector<string> &tags, string notes);

    virtual ~Event() noexcept = default;

    [[nodiscard]] virtual shared_ptr<Event> clone() const = 0;

    virtual ostream &print(ostream &out) const = 0;

    void setStart(const Datetime &start);

    [[nodiscard]] size_t getId() const;

    [[nodiscard]] virtual bool isConflict(const Event &event, int offsetHours) const = 0;
protected:
    size_t mEventId;
    string mName;
    Datetime mStart;
    string mPlace;
    vector<string> mAttendees;
    vector<string> mTags;
    string mNotes;
};

std::ostream &operator<<(std::ostream &out, const Event &self);
