//
// Created by Anon user on 10.05.2023.
//
#include "eventRecurring.h"

EventRecurring::EventRecurring(size_t eventId, const Datetime &start, const string &place,
                               const vector<string> &attendees, const set<string> &tags, const string &notes):
                               EventSimple(eventId, start, Datetime(0, 0, 0, 0, 0), place, attendees, tags, notes) {}

shared_ptr<Event> EventRecurring::clone() const {
    return std::make_shared<EventRecurring>(*this);
}
