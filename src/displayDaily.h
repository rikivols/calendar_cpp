
#pragma once

#include "displayCalendar.h"

class DisplayDaily: public DisplayCalendar {
public:
    DisplayDaily();

    [[nodiscard]] shared_ptr<DisplayCalendar> clone() const override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;

private:
    size_t mMonth;
    size_t mDay;
};