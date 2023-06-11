
#pragma once

#include "CEvent.h"

/**
 * Represents calendar's event that repeats every day. It has a start datetime, but it doesn't have the end date,
 * only time.
 */
class CEventRecurring : public CEvent {
public:
    CEventRecurring(size_t eventId, string name, const CDatetime &start, const CTime &end, string place,
                    const vector<string> &attendees, const vector<string> &tags, string notes);

    CEventRecurring(const CEventRecurring &eventRecurring);

    CEventRecurring(CEventRecurring &&eventRecurring) noexcept;

    CEventRecurring &operator=(CEventRecurring eventRecurring);

    [[nodiscard]] shared_ptr<CEvent> clone() const override;

    ostream &print(ostream &out) const override;

    /**
     * Gets event's end. Since Recurring events don't have an end, only event time will be returned with dummy values.
     *
     * @return End datetime of the event.
     */
    [[nodiscard]] CDatetime getEnd() const override;

    /**
     * Gets absolute value of the event's duration.
     *
     * @return absolute value of the event's duration.
     */
    [[nodiscard]] int getEventDuration() const override;

    /**
     * Check if event's datetime is valid and if their duration (is non 0) is valid.
     *
     * @return true = event's datetime is valid, false = aren't
     */
    [[nodiscard]] bool areEventDatesOk() const override;

    /**
    * Checks whether event happens on that day.
    *
    * @param year year that event should happen on
    * @param month month that event should happen on
    * @param day day that event should happen on
    * @return true = happens, false = doesn't happen
    */
    [[nodiscard]] bool happensOnDay(int year, int month, int day) const override;

    /**
    * Get a time range that will be forever busy from that point on. Only applies for recurring events since they
    * repeat every day. So gets start and end time of an event here.
    *
    * @return time range that will be forever busy from that point on
    */
    [[nodiscard]] pair<CTime, CTime> getForeverBusyTime() const override;

    /**
     * Sets event's time to the given time.
     *
     * @param end given datetime to set the event's end time to
     */
    void setEnd(const CDatetime &end) override;

    [[nodiscard]] bool isRecurring() const override;

    /**
     * Finds out if calendar's event doesn't conflict with the provided event. Since recurring event repeats every
     * day and doesn't have the end, the calculation will be different.
     *
     * @param event the event we want to check, whether it conflicts with the class's event
     * @param offsetHours if we want to add or subtract hours of the provided event's datetime for searching of
     *                    the conflict, used for checking conflict when moving event
     * @return true = event conflicts, false = event doesn't conflict
     */
    [[nodiscard]] bool isConflict(const CEvent &event, int offset) const override;

    /**
     * Export event into a file row to be stored.
     *
     * @param fileRow string to store the event export to.
     * @return event in a one line string export form
     */
    string &exportEvent(string &fileRow) const override;

private:
    CTime mEnd;
};
