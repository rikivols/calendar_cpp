
#pragma once

#include <set>
#include <string>
#include <vector>

#include "CEvent.h"

/**
 * Represents calendar's event that doesn't repeat.
 */
class CEventSimple: public CEvent {
public:
    CEventSimple(size_t eventId, string name, const CDatetime &start, const CDatetime &end, string place, const vector<string> &attendees,
                const vector<string> &tags, string note);

    [[nodiscard]] shared_ptr<CEvent> clone() const override;

    ostream &print(ostream &out) const override;

    /**
     * Replaces the current end of the event by the provided datetime.
     *
     * @param[in] datetime Datetime we want to have at end
     */
    void setEnd(const CDatetime & datetime);

    [[nodiscard]] CDatetime & getEnd() const override;

    /**
     * Finds out if calendar's event doesn't conflict with the provided event.
     *
     * @param[in] event the event we want to check, whether it conflicts with the class's event
     * @param[in] offsetHours if we want to add or subtract hours of the provided event's datetime for searching of
     *                        the conflict, used for checking conflict when moving event
     * @return true = event conflicts, false = event doesn't conflict
     */
    [[nodiscard]] bool isConflict(const CEvent &event, int offsetHours) const override;

    [[nodiscard]] pair<CTime, CTime> getForeverBusyTime() const override;

private:
    CDatetime mEnd;
};
