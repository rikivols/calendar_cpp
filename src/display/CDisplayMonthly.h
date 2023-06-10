
#pragma once

#include "CDisplayCalendar.h"

class CDisplayMonthly : public CDisplayCalendar {
public:
    CDisplayMonthly() = default;

    [[nodiscard]] shared_ptr<CDisplayCalendar> clone() const override;

    void refreshCurrentPage() override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;
};