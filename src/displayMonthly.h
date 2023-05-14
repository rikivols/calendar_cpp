
#pragma once

#include "displayCalendar.h"

class DisplayMonthly: public DisplayCalendar {
public:
    DisplayMonthly();

    [[nodiscard]] shared_ptr<DisplayCalendar> clone() const override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;

private:
    size_t mYear;
    size_t mMonth;
};