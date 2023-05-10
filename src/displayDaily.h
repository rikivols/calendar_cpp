#include "displayCalendar.h"
#include "event.h"

class DisplayDaily: public DisplayCalendar {
public:
    DisplayDaily(const map<size_t, shared_ptr<Event>> &events);

    [[nodiscard]] shared_ptr<DisplayCalendar> clone() const override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;

private:
    size_t mMonth;
    size_t mDay;
};