#include "testCalendarOperations.h"


void testCalendarOperations() {
    bool isSuccess;
    auto rec1 = CEventRecurring(1, "", CDatetime(2023, 5, 5, 15, 0), CTime(17, 0), "", {}, {}, "");
    auto rec2 = CEventRecurring(2, "", CDatetime(2023, 5, 5, 18, 0), CTime(23, 30), "", {}, {}, "");
    auto rec3 = CEventRecurring(3, "", CDatetime(2023, 5, 5, 23, 31), CTime(5, 30), "", {}, {}, "");
    auto rec4 = CEventRecurring(4, "", CDatetime(2023, 5, 5, 5, 45), CTime(7, 30), "", {}, {}, "");
    auto rec5 = CEventRecurring(5, "", CDatetime(2023, 5, 5, 8, 32), CTime(11, 30), "", {}, {}, "");
    auto rec6 = CEventRecurring(6, "", CDatetime(2023, 5, 5, 12, 30), CTime(14, 30), "", {}, {}, "");

    CCalendar calendar;
    isSuccess = calendar.addEvent(rec1, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(rec2, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(rec3, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(rec4, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(rec5, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(rec6, true);
    assert(isSuccess == true);

    isSuccess = calendar.moveEvent(1, 1);
    assert(isSuccess == false);

    isSuccess = calendar.removeEvent(2);
    assert(isSuccess == true);

    isSuccess = calendar.moveEvent(1, 2);
    assert(isSuccess == true);
    assert(calendar.getEvent(1)->getEnd().getHour() == 19);

    isSuccess = calendar.moveEvent(1, -2);
    assert(isSuccess == true);
    assert(calendar.getEvent(1)->getEnd().getHour() == 17);

}
