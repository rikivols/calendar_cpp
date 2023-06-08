
#include "CCalendarFinder.h"

#include <utility>


CCalendarFinder::CCalendarFinder(CCalendar calendar, bool isAnd, string name, const CDatetime &start, const CDatetime &end,
                               string place, const vector<string> &attendees, const vector<string> &tags
                               ): mName(std::move(name)), mPlace(std::move(place)), mStart(start), mEnd(end),
                                  mAttendees(attendees), mTags(tags), mIsAnd(isAnd), mCalendar(std::move(calendar)) {}


bool CCalendarFinder::findEvents() {
    vector<shared_ptr<CEvent>> tempEvents;
    bool isFirst = true;

    if (!mName.empty()) {
        findByString(tempEvents, mName, 1);
        updateFinalEvents(mEventsResult, tempEvents, isFirst);
    }
    if (mStart.isValidDate()) {
        findByDate(tempEvents, mStart, true);
        updateFinalEvents(mEventsResult, tempEvents, isFirst);
    }
    if (mEnd.isValidDate()) {
        findByDate(tempEvents, mEnd, false);
        updateFinalEvents(mEventsResult, tempEvents, isFirst);
    }
    if (!mPlace.empty()) {
        findByString(tempEvents, mPlace, 2);
        updateFinalEvents(mEventsResult, tempEvents, isFirst);
    }
    if (!mAttendees.empty()) {
        findByVector(tempEvents, mAttendees, 1);
        updateFinalEvents(mEventsResult, tempEvents, isFirst);
    }
    if (!mTags.empty()) {
        findByVector(tempEvents, mTags, 2);
        updateFinalEvents(mEventsResult, tempEvents, isFirst);
    }

    cout << "Number of found calendar events: " << mEventsResult.size() << endl;

    return !mEventsResult.empty();
}


void CCalendarFinder::printEvents() {
    sort(mEventsResult.begin(), mEventsResult.end(), CEvent::sortEventsByStartDatetime);

    for (const auto &event: mEventsResult) {
        cout << *event;
    }
}


void CCalendarFinder::exportEvents() {
    CEventExporter exporter(mEventsResult);
    exporter.exportToFile("calendarFindExport");
}


void CCalendarFinder::findByString(vector<shared_ptr<CEvent>> &events, const string &toMatch, int stringOption) const {
    for (auto &event: mCalendar.getSortedEvents(nullptr, true)) {
        if (stringOption == 1 && event->nameEquals(toMatch)) {
            events.push_back(event);
        }
        if (stringOption == 2 && event->placeEquals(toMatch)) {
            events.push_back(event);
        }
    }
}

void CCalendarFinder::findByDate(vector<shared_ptr<CEvent>> &events, const CDatetime &date, bool isStart) const {
    for (auto &event: mCalendar.getSortedEvents(nullptr, true)) {
        if (isStart && event->getStart() >= date) {
            events.push_back(event);
        }
        if (!isStart && event->getStart() + event->getEventDuration() <= date) {
            events.push_back(event);
        }
    }
}

void CCalendarFinder::findByVector(vector<shared_ptr<CEvent>> &events, const vector<string> &vec, int vectorOption) const {
    for (auto &event: mCalendar.getSortedEvents(nullptr, true)) {
        if (vectorOption == 1 && event->isInAttendees(vec)) {
            events.push_back(event);
        }
        if (vectorOption == 2 && event->isInTags(vec)) {
            events.push_back(event);
        }
    }
}


void CCalendarFinder::updateFinalEvents(vector<shared_ptr<CEvent>> &finalEvents,
                                        const vector<shared_ptr<CEvent>> &tempEvents, bool &isFirst) const {
    if (mIsAnd && !isFirst) {
        finalEvents = getIntersection(finalEvents, tempEvents);
    }
    else {
        finalEvents = getUnion(finalEvents, tempEvents);
    }

    isFirst = false;
}


vector<shared_ptr<CEvent>> getIntersection(const vector<shared_ptr<CEvent>> &v1, const vector<shared_ptr<CEvent>> &v2) {
    vector<shared_ptr<CEvent>> result;

    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result), CEvent::sortEventsById);

    return result;
}


vector<shared_ptr<CEvent>> getUnion(const vector<shared_ptr<CEvent>> &v1, const vector<shared_ptr<CEvent>> &v2) {
    vector<shared_ptr<CEvent>> finalObject;

    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(finalObject), CEvent::sortEventsById);

    return finalObject;
}
