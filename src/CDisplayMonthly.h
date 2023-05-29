
#pragma once

#include "CDisplayCalendar.h"

class CDisplayMonthly : public CDisplayCalendar {
public:
    CDisplayMonthly();

    [[nodiscard]] shared_ptr<CDisplayCalendar> clone() const override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;

private:
    size_t mMonth;
};