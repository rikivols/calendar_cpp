
#include "displayCalendar.h"

class DisplayMonthly: public DisplayCalendar {
public:
    DisplayMonthly(const Calendar & calendar);

    [[nodiscard]] shared_ptr<DisplayCalendar> clone() const override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;

private:
    size_t mYear;
    size_t mMonth;
};