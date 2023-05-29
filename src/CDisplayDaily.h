
#pragma once

#include "CDisplayCalendar.h"

class CDisplayDaily : public CDisplayCalendar {
public:
    CDisplayDaily();

    [[nodiscard]] shared_ptr<CDisplayCalendar> clone() const override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;

private:
    size_t mMonth;
    size_t mDay;
};