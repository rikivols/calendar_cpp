#include "displayDaily.h"

DisplayDaily::DisplayDaily(const map<size_t, shared_ptr<Event>> &events) {
    auto now = getTimeNow();

    mYear = now->tm_year + 1900;
    mMonth = now->tm_mon + 1;
    mDay = now->tm_mday;
    mEvents = events;
}

shared_ptr<DisplayCalendar> DisplayDaily::clone() const {
    return make_shared<DisplayDaily>(*this);
}
