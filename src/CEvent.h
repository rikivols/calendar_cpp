
#pragma once

#include <iostream>

#include "CDatetime.h"

/**
 * Abstract class of the calendar's event.
 */
class CEvent {
public:
    CEvent(size_t eventId, string name, const CDatetime &start, string place,
          const vector<string> &attendees, const vector<string> &tags, string notes);

    virtual ~CEvent() noexcept = default;

    [[nodiscard]] virtual shared_ptr<CEvent> clone() const = 0;

    virtual ostream &print(ostream &out) const = 0;

    void setStart(const CDatetime &start);

    [[nodiscard]] size_t getId() const;

    [[nodiscard]] virtual bool isConflict(const CEvent &event, int offsetHours) const = 0;
protected:
    size_t mEventId;
    string mName;
    CDatetime mStart;
    string mPlace;
    vector<string> mAttendees;
    vector<string> mTags;
    string mNotes;
};

std::ostream &operator<<(std::ostream &out, const CEvent &self);
