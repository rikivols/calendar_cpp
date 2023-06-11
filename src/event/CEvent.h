
#pragma once

#include <iostream>

#include "../utils/CDatetime.h"


/**
 * Abstract class of the calendar's event. Serves as a base for simple and recurring events.
 *
 * Those 2 events differ with the end datetime (for recurring it's only a time) and different display/calculations of
 * when that event occurs.
 */
class CEvent {
public:
    /**
     * Initializes all event values except the event end. That has to be initialized by the child classes
     *
     * @param eventId id of an event
     * @param name string name of the event
     * @param start start datetime of the event
     * @param place place where the event happens
     * @param attendees attendees of the event
     * @param tags tags of the event
     * @param notes optional notes for the event
     */
    CEvent(size_t eventId, string name, const CDatetime &start, string place,
           const vector<string> &attendees, const vector<string> &tags, string notes);

    CEvent(const CEvent &event);

    CEvent(CEvent &&event) noexcept;

    virtual ~CEvent() noexcept = default;

    CEvent &operator=(const CEvent &element) = delete;

    CEvent &operator=(CEvent &&element) = delete;

    [[nodiscard]] virtual shared_ptr<CEvent> clone() const = 0;

    virtual ostream &print(ostream &out) const = 0;

    /**
     * Puts The last part of the event display to ostream.
     *
     * @param out ostream to add display to
     * @return newly added ostream
     */
    ostream &partialPrint(ostream &out) const;

    [[nodiscard]] size_t getId() const;

    [[nodiscard]] CDatetime getStart() const;

    /**
     * Gets event's end. If it's a recurring event, only event time will be returned with dummy values.
     *
     * @return End datetime of the event.
     */
    [[nodiscard]] virtual CDatetime getEnd() const = 0;

    /**
     * Gets absolute value of the event's duration.
     *
     * @return absolute value of the event's duration.
     */
    [[nodiscard]] virtual int getEventDuration() const = 0;

    /**
     * Get a time range that will be forever busy from that point on. Only applies for recurring events since they
     * repeat every day.
     *
     * @return time range that will be forever busy from that point on
     */
    [[nodiscard]] virtual pair<CTime, CTime> getForeverBusyTime() const = 0;

    void setStart(const CDatetime &start);

    /**
     * Sets event's datetime or time to the given datetime/time.
     *
     * @param end given datetime to set the event's end to
     */
    virtual void setEnd(const CDatetime &end) = 0;

    /**
     * Checks if event's name exactly matches with the given name.
     *
     * @param name name to match
     * @return true = match, false = doesn't
     */
    bool nameEquals(const string &name);

    /**
     * Checks if event's place exactly matches with the given place.
     *
     * @param place place to match
     * @return true = match, false = doesn't
     */
    bool placeEquals(const string &place);

    /**
     * Checks if the entire given attendees content is in the event's attendees.
     *
     * @param attendees attendees to check
     * @return true = all given attendees in event, false = NOT all given attendees in event
     */
    bool isInAttendees(const vector<string> &attendees);

    /**
     * Checks if the entire given tags content is in the event's tags.
     *
     * @param tags tags to check
     * @return true = all given tags in event, false = NOT all given tags in event
     */
    bool isInTags(const vector<string> &tags);

    [[nodiscard]] virtual bool isRecurring() const = 0;

    /**
     * Check if event's datetime is valid and if their duration is valid.
     *
     * @return true = event's datetime is valid, false = aren't
     */
    [[nodiscard]] virtual bool areEventDatesOk() const = 0;

    /**
     * Checks whether event happens on that day.
     *
     * @param year year that event should happen on
     * @param month month that event should happen on
     * @param day day that event should happen on
     * @return true = happens, false = doesn't happen
     */
    [[nodiscard]] virtual bool happensOnDay(int year, int month, int day) const = 0;

    /**
     * Checks whether event's time conflicts with the given event + offset in hours. Conflicts means that it happens at
     * the same time and can't be added to the calendar.
     *
     * @param event event to check conflict with
     * @param offset by how many hours we should move the event's dates before checking for conflict
     * @return
     */
    [[nodiscard]] virtual bool isConflict(const CEvent &event, int offset) const = 0;

    /**
     * Export event into a file row to be stored.
     *
     * @param fileRow string to store the event export to.
     * @return event in a one line string export form
     */
    virtual string &exportEvent(string &fileRow) const = 0;

    static bool sortEventsByStartDatetime(const shared_ptr<CEvent> &event1, const shared_ptr<CEvent> &event2);

    static bool sortEventsById(const shared_ptr<CEvent> &event1, const shared_ptr<CEvent> &event2);

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
