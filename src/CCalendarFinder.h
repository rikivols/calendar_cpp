
#pragma once

#include "utils/CDatetime.h"
#include "CCalendar.h"
#include "importExport/CEventExporter.h"

#include <map>
#include <utility>

using namespace std;


class CCalendarFinder {
public:
    /**
     * Initialize finder by the values we want to find by
     *
     * @param calendar calendar to find in
     * @param isAnd if it's AND or OR clause between inputs
     * @param name name to find the element by
     * @param start start of our event has to come after the given start (or at that time)
     * @param end event has to end before our the given datetime
     * @param mPlace place to find the element by
     * @param attendees attendees to find the element by
     * @param tags tags to find the element by
     */
    CCalendarFinder(CCalendar calendar, bool isAnd, string name, const CDatetime &start, const CDatetime &end, string mPlace,
                   const vector<string> &attendees, const vector<string> &tags);

    /**
     * Find the event based on the given criteria, store them to mEventsResult
     *
     * @return found events based on the given criteria.
     */
    bool findEvents();

    /**
     * Print the found events
     */
    void printEvents();

    /**
     * Export the found events
     */
    void exportEvents();

private:
    /**
     * Search events by a string of an exact match
     *
     * @param events found events
     * @param toMatch string to match
     * @param stringOption which event's string to search by
     */
    void findByString(vector<shared_ptr<CEvent>> &events, const string &toMatch, int stringOption) const;

    /**
    * Search events by a the given start or end of the date
    *
    * @param events found events
    * @param date date to search by
    * @param isStart if searching by start or end of an event
    */
    void findByDate(vector<shared_ptr<CEvent>> &events, const CDatetime &date, bool isStart) const;

    /**
     * Find events by a given vector values. All vector values must be present in the event
     *
     * @param events found events
     * @param vec vector to search by
     * @param vectorOption which vector to search in
     */
    void findByVector(vector<shared_ptr<CEvent>> &events, const vector<string> &vec, int vectorOption) const;

    /**
     * Decide if we want to do union or intersection
     *
     * @param finalEvents result of union or intersection operation
     * @param tempEvents events to union/intersect with
     * @param isFirst whether it's the first intersection/union operation
     */
    void updateFinalEvents(vector<shared_ptr<CEvent>> &finalEvents, const vector<shared_ptr<CEvent>> &tempEvents,
                           bool &isFirst) const;

    string mName, mPlace, mNote;
    CDatetime mStart, mEnd;
    vector<string> mAttendees, mTags;
    bool mIsAnd;
    vector<shared_ptr<CEvent>> mEventsResult;  // found events
    CCalendar mCalendar;
};


vector<shared_ptr<CEvent>> getIntersection(const vector<shared_ptr<CEvent>> &v1, const vector<shared_ptr<CEvent>> &v2);

vector<shared_ptr<CEvent>> getUnion(const vector<shared_ptr<CEvent>> &v1, const vector<shared_ptr<CEvent>> &v2);