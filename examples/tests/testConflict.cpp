#include "testConflict.h"


void testConflictRecurring() {
    bool isSuccess;

    auto recEvent = CEventRecurring(1, "", CDatetime(2023, 5, 5, 15, 0),  CTime(17, 0), "", {}, {}, "");
    CCalendar calendar;
    isSuccess = calendar.addEvent(recEvent, true);
    assert(isSuccess == true);
    CConflictSolver solver(calendar, 1);

    // find the closest date
    auto freeDatetime = solver.getNextFreeDatetime(50, CDatetime(2023, 5, 5, 14, 20));
    assert(freeDatetime == CDatetime(2023, 5, 5, 17, 1));

    // the closest date is right now
    auto freeDatetime2 = solver.getNextFreeDatetime(50, CDatetime(2023, 5, 5, 14, 0));
    assert(freeDatetime2 == CDatetime(2023, 5, 5, 14, 0));

    auto rec2 = CEventRecurring(2, "", CDatetime(2023, 5, 5, 18, 0),  CTime(23, 30), "", {}, {}, "");
    isSuccess = calendar.addEvent(rec2, true);
    assert(isSuccess == true);

    // find a date that's 2 events in the future
    CConflictSolver solver2(calendar, 1);
    auto freeDatetime3 = solver2.getNextFreeDatetime(70, CDatetime(2023, 5, 5, 14, 10));
    assert(freeDatetime3 == CDatetime(2023, 5, 5, 23, 31));

    auto rec3 = CEventRecurring(3, "", CDatetime(2023, 5, 5, 23, 31),  CTime(5, 30), "", {}, {}, "");
    calendar.addEvent(rec3, true);

    // find next free datetime that is one day in the future
    CConflictSolver solver3(calendar, 1);
    auto freeDatetime4 = solver3.getNextFreeDatetime(70, CDatetime(2023, 5, 5, 14, 10));
    assert(freeDatetime4 == CDatetime(2023, 5, 6, 5, 31));

    auto rec4 = CEventRecurring(4, "", CDatetime(2023, 5, 5, 5, 45),  CTime(7, 30), "", {}, {}, "");
    auto rec5 = CEventRecurring(5, "", CDatetime(2023, 5, 5, 8, 32),  CTime(11, 30), "", {}, {}, "");
    auto rec6 = CEventRecurring(6, "", CDatetime(2023, 5, 5, 12, 30),  CTime(14, 30), "", {}, {}, "");
    isSuccess = calendar.addEvent(rec4, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(rec5, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(rec6, true);
    assert(isSuccess == true);

    // make it impossible to find the next date
    CConflictSolver solver4(calendar, 1);
    auto freeDatetime5 = solver4.getNextFreeDatetime(70, CDatetime(2023, 5, 5, 14, 10));
    assert(freeDatetime5.isValidDate() == false);

    // we can still barely fit 1 more event that's shorter
    auto freeDatetime6 = solver4.getNextFreeDatetime(60, CDatetime(2023, 5, 5, 14, 10));
    assert(freeDatetime6 == CDatetime(2023, 5, 6, 7, 31));
}


void testConflictMix() {
    bool isSuccess;

    auto rec1 = CEventRecurring(1, "", CDatetime(2023, 5, 5, 14, 0),  CTime(17, 35), "", {}, {}, "");
    auto sim1 = CEventSimple(2, "", CDatetime(2023, 5, 6, 18, 0),  CDatetime(2023, 5, 6, 19, 0), "", {}, {}, "");
    auto sim2 = CEventSimple(3, "", CDatetime(2023, 5, 6, 20, 0),  CDatetime(2023, 5, 6, 23, 0), "", {}, {}, "");

    CCalendar calendar;
    isSuccess = calendar.addEvent(rec1, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(sim1, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(sim2, true);
    assert(isSuccess == true);

    CConflictSolver solver1(calendar, 1);

    auto freeDatetime1 = solver1.getNextFreeDatetime(60, CDatetime(2023, 5, 6, 13, 10));
    cout << "free datetime: " << freeDatetime1 << endl;
    assert(freeDatetime1 == CDatetime(2023, 5, 6, 23, 1));

    auto sim3 = CEventSimple(4, "", CDatetime(2023, 5, 7, 0, 25),  CDatetime(2023, 5, 7, 13, 59), "", {}, {}, "");
    auto sim4 = CEventSimple(5, "", CDatetime(2023, 5, 7, 17, 38),  CDatetime(2023, 5, 8, 13, 55), "", {}, {}, "");
    auto sim5 = CEventSimple(6, "", CDatetime(2023, 5, 8, 17, 59),  CDatetime(2023, 5, 8, 23, 59), "", {}, {}, "");

    isSuccess = calendar.addEvent(sim3, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(sim4, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(sim5, true);
    assert(isSuccess == true);

    CConflictSolver solver2(calendar, 1);
    auto freeDatetime2 = solver2.getNextFreeDatetime(60, CDatetime(2023, 5, 6, 13, 10));
    assert(freeDatetime2 == CDatetime(2023, 5, 6, 23, 1));

    // find several days in the future
    auto freeDatetime3 = solver2.getNextFreeDatetime(90, CDatetime(2023, 5, 6, 13, 10));
    assert(freeDatetime3 == CDatetime(2023, 5, 9, 0, 0));

}


void testLongEvents() {
    bool isSuccess;

    auto sim1 = CEventSimple(1, "", CDatetime(2023, 5, 18, 0, 0),  CDatetime(2023, 5, 25, 0, 0), "", {}, {}, "");
    auto sim2 = CEventSimple(2, "", CDatetime(2023, 5, 27, 20, 0),  CDatetime(2023, 5, 30, 5, 0), "", {}, {}, "");
    auto sim3 = CEventSimple(3, "", CDatetime(2023, 6, 5, 20, 0),  CDatetime(2023, 7, 11, 5, 0), "", {}, {}, "");

    CCalendar calendar;
    isSuccess = calendar.addEvent(sim1, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(sim2, true);
    assert(isSuccess == true);
    isSuccess = calendar.addEvent(sim3, true);
    assert(isSuccess == true);

    CConflictSolver solver1(calendar, 1);

    auto freeDatetime1 = solver1.getNextFreeDatetime(DAY_MINUTES*5, CDatetime(2023, 5, 13, 13, 10));
    assert(freeDatetime1 == CDatetime(2023, 5, 30, 5, 1));

    auto freeDatetime2 = solver1.getNextFreeDatetime(DAY_MINUTES*6, CDatetime(2023, 5, 13, 13, 10));
    assert(freeDatetime2 == CDatetime(2023, 5, 30, 5, 1));

    auto freeDatetime3 = solver1.getNextFreeDatetime(DAY_MINUTES*7, CDatetime(2023, 5, 13, 13, 10));
    assert(freeDatetime3 == CDatetime(2023, 7, 11, 5, 1));

}
