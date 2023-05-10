
#include "displayCalendar.h"

class DisplayDaily: public DisplayCalendar {
public:
    DisplayDaily();

    void display() const override;

    void nextPage() override;

    void previousPage() override;

protected:
    size_t curYear;
private:
    size_t curMonth;
    size_t curDay;
};