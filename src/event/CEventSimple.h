
#pragma once

#include <set>
#include <string>
#include <vector>

#include "CEvent.h"

/**
 * Represents calendar's event that happens only once. It has a start datetime, and end datetime.
 */
class CEventSimple: public CEvent {
public:
    CEventSimple(size_t eventId, string name, const CDatetime &start, const CDatetime &end, string place, const vector<string> &attendees,
                const vector<string> &tags, string note);

    CEventSimple(const CEventSimple &CEventSimple);

    CEventSimple(CEventSimple &&CEventSimple) noexcept;

    CEventSimple &operator=(CEventSimple eventRecurring);

    [[nodiscard]] shared_ptr<CEvent> clone() const override;

    ostream &print(ostream &out) const override;

    /**
     * Gets event's end datetime.
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
     * Check if event's datetime is valid and if their duration (non negative) is valid.
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
    * repeat every day. So gets just dummy values here that are not valid.
    *
    * @return time range that will be forever busy from that point on
    */
    [[nodiscard]] pair<CTime, CTime> getForeverBusyTime() const override;

    /**
     * Replaces the current end of the event by the provided datetime.
     *
     * @param datetime datetime to set at the end of the event
     */
    void setEnd(const CDatetime & datetime) override;

    [[nodiscard]] bool isRecurring() const override;

    /**
     * Finds out if calendar's event doesn't conflict with the provided event.
     *
     * @param event the event we want to check, whether it conflicts with the class's event
     * @param offsetHours if we want to add or subtract hours of the provided event's datetime for searching of
     *                    the conflict, used for checking conflict when moving event
     * @return true = event conflicts, false = event doesn't conflict
     */
    [[nodiscard]] bool isConflict(const CEvent & event, int offset) const override;

    string & exportEvent(string &fileRow) const override;


private:
    CDatetime mEnd;
};
