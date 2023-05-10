
#include "displayCalendar.h"

class DisplayWeekly: public DisplayCalendar {
public:
    DisplayWeekly(const map<size_t, shared_ptr<Event>> &events);

    [[nodiscard]] shared_ptr<DisplayCalendar> clone() const override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;

private:
    size_t mYear;
    size_t mWeek;
};