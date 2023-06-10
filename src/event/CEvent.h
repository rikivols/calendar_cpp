
#pragma once

#include <iostream>

#include "../utils/CDatetime.h"

/**
 * Abstract class of the calendar's event.
 */
class CEvent {
public:
    CEvent(size_t eventId, string name, const CDatetime &start, string place,
          const vector<string> &attendees, const vector<string> &tags, string notes);

    CEvent(const CEvent &event);

    virtual ~CEvent() noexcept = default;

    CEvent &operator=(const CEvent &element) = delete;

    CEvent &operator=(CEvent &&element) = delete;

    [[nodiscard]] virtual shared_ptr<CEvent> clone() const = 0;

    virtual ostream &print(ostream &out) const = 0;

    ostream &partialPrint(ostream &out) const;

    [[nodiscard]] CDatetime getStart() const;

    [[nodiscard]] virtual bool happensOnDay(int year, int month, int day) const = 0;

    virtual string &exportEvent(string &fileRow) const = 0;

    void setStart(const CDatetime &start);

    virtual void setEnd(const CDatetime &end) = 0;

    bool nameEquals(const string &name);

    bool placeEquals(const string &place);

    bool isInAttendees(const vector<string> &attendees);

    bool isInTags(const vector<string> &tags);

    [[nodiscard]] virtual CDatetime getEnd() const = 0;

    [[nodiscard]] virtual CTime getEndTime() const = 0;

    [[nodiscard]] virtual int getEventDuration() const = 0;

    [[nodiscard]] size_t getId() const;

    [[nodiscard]] virtual bool isConflict(const CEvent & event, int offset) const = 0;

    [[nodiscard]] virtual pair<CTime, CTime> getForeverBusyTime() const = 0;

    static bool sortEventsByStartDatetime(const shared_ptr<CEvent>& event1, const shared_ptr<CEvent>& event2);

    static bool sortEventsById(const shared_ptr<CEvent>& event1, const shared_ptr<CEvent>& event2);

protected:
    void swapEvent(CEvent &event);

    size_t mEventId;
    string mName;
    CDatetime mStart;
    string mPlace;
    vector<string> mAttendees;
    vector<string> mTags;
    string mNotes;
};

std::ostream &operator<<(std::ostream &out, const CEvent &self);
