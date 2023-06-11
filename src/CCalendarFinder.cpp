
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
                                        vector<shared_ptr<CEvent>> &tempEvents, bool &isFirst) const {
    if (mIsAnd && !isFirst) {
        finalEvents = getIntersectionUnion(tempEvents, tempEvents, true);
    }
    else {
        finalEvents = getIntersectionUnion(tempEvents, tempEvents, false);
    }

    tempEvents.clear();

    isFirst = false;
}


vector<shared_ptr<CEvent>> getIntersectionUnion(const vector<shared_ptr<CEvent>> &v1, const vector<shared_ptr<CEvent>> &v2, bool isIntersection) {
    vector<shared_ptr<CEvent>> finalObject;
    vector<size_t> idsObject;

    vector<size_t> idsV1;
    vector<size_t> idsV2;

    for (const auto &v: v1) {
        idsV1.push_back(v->getId());
    }

    for (const auto &v: v2) {
        idsV2.push_back(v->getId());
    }

    sort(idsV1.begin(), idsV1.end());
    sort(idsV2.begin(), idsV2.end());

    if (isIntersection) {
        set_intersection(idsV1.begin(), idsV1.end(), idsV2.begin(), idsV2.end(), back_inserter(idsObject));
    }
    else {
        set_union(idsV1.begin(), idsV1.end(), idsV2.begin(), idsV2.end(), back_inserter(idsObject));
    }

    bool toBreak = false;

    for (auto eventId: idsObject) {
        for (const auto &val1: v1) {
            if (eventId == val1->getId()) {
                finalObject.push_back(val1);
                toBreak = true;
                break;
            }
        }

        if (toBreak) {
            toBreak = false;
            continue;
        }

        for (const auto &val2: v2) {
            if (eventId == val2->getId()) {
                finalObject.push_back(val2);
                break;
            }
        }
    }

    return finalObject;
}
