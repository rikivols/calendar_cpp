#include <ctime>
#include "calendar.h"

tm *getTimeNow() {
    time_t cTime = time(nullptr);
    return localtime(&cTime);
}

class DisplayCalendar {
public:
    virtual ~DisplayCalendar() noexcept = default;

    [[nodiscard]] virtual shared_ptr<DisplayCalendar> clone() const = 0;

    virtual void display() const = 0;

    virtual void nextPage() = 0;

    virtual void previousPage() = 0;
protected:
    Calendar mCalendar;
    size_t mYear;
};
