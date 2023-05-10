
#include "calendar.h"

class DisplayCalendar: public Calendar {
public:
    virtual ~DisplayCalendar() noexcept = default;

    virtual shared_ptr<DisplayCalendar> clone() const = 0;

    virtual void display() const = 0;

    virtual void nextPage() = 0;

    virtual void previousPage() = 0;
};
