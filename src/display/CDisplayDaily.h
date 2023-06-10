
#pragma once

#include "CDisplayCalendar.h"

class CDisplayDaily : public CDisplayCalendar {
public:
    CDisplayDaily() = default;

    [[nodiscard]] unique_ptr<CDisplayCalendar> clone() const override;

    void refreshCurrentPage() override;

    void display() const override;

    void nextPage() override;

    void previousPage() override;
};