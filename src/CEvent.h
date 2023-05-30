
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

    [[nodiscard]] CDatetime getStart() const;

    void setStart(const CDatetime &start);

    virtual void setEnd(const CDatetime &end) = 0;

    [[nodiscard]] virtual CDatetime getEnd() const = 0;

    [[nodiscard]] virtual CTime getEndTime() const = 0;

    [[nodiscard]] virtual size_t getEventDuration() const = 0;

    [[nodiscard]] size_t getId() const;

    [[nodiscard]] virtual bool isConflict(const CEvent & event, int offsetHours) const = 0;

    [[nodiscard]] virtual pair<CTime, CTime> getForeverBusyTime() const = 0;

    static bool sortEventsByStartDatetime(const shared_ptr<CEvent>& event1, const shared_ptr<CEvent>& event2);

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
