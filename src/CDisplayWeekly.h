
#pragma once

#include "CDisplayCalendar.h"

class CDisplayWeekly : public CDisplayCalendar {
public:
    CDisplayWeekly();

    [[nodiscard]] shared_ptr<CDisplayCalendar> clone() const override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;

private:
    int mWeek;
};