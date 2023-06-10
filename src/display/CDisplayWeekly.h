
#pragma once

#include "CDisplayCalendar.h"

class CDisplayWeekly : public CDisplayCalendar {
public:
    CDisplayWeekly() = default;

    [[nodiscard]] shared_ptr<CDisplayCalendar> clone() const override;

    void refreshCurrentPage() override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;

};