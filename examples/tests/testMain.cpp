#include "testDates.h"
#include "testConflict.h"
#include "testCalendarOperations.h"


int main() {
    testDateValid();
    cout << endl << "Date validation test PASSED" << endl;
    testOperations();
    cout << endl << "Date arithmetic operations test PASSED" << endl;
    testConflictRecurring();
    cout << endl << "Event recurring conflict resolution test PASSED" << endl;
    testConflictMix();
    cout << endl << "Event simple and recurring conflict resolution test PASSED" << endl;
    testLongEvents();
    cout << endl << "Long events simple conflict resolution test PASSED" << endl;
    testCalendarOperations();
    cout << endl << "Calendar operations (adding, moving, removing) test PASSED" << endl;

}