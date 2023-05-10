#include "displayMonthly.h"

DisplayMonthly::DisplayMonthly(const map<size_t, shared_ptr<Event>> &events) {
    auto now = getTimeNow();

    mYear = now->tm_year + 1900;
    mMonth = now->tm_mon + 1;
    mEvents = events;
}

shared_ptr<DisplayCalendar> DisplayMonthly::clone() const {
    return make_shared<DisplayMonthly>(*this);
}
