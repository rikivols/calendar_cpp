
#pragma once

#include <iostream>

#include "datetime.h"

/**
 * Abstract class of the calendar's event.
 */
class Event {
public:
    virtual ~Event() noexcept = default;

    [[nodiscard]] virtual shared_ptr<Event> clone() const = 0;

    virtual ostream &print(ostream &out) const = 0;

    virtual void setStart(const Datetime &datetime) = 0;

    virtual void setEnd(const Datetime &datetime) = 0;

    [[nodiscard]] virtual size_t getId() const = 0;

    [[nodiscard]] virtual bool isConflict(const Event &event, int offsetHours) const = 0;
};

std::ostream &operator<<(std::ostream &out, const Event &self);
