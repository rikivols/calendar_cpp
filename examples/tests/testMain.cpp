#include "testDates.h"
#include "testConflict.h"
#include "testCalendarOperations.h"


int main() {
    testDateValid();
    cout << "Date validation test passed" << endl;
    testOperations();
    cout << "Date arithmetic operations test passed" << endl;
    testConflictRecurring();
    cout << "Event recurring conflict resolution test passed" << endl;
    testConflictMix();
    cout << "Event simple and recurring conflict resolution test passed" << endl;
    testLongEvents();
    cout << "Long events simple conflict resolution test passed" << endl;
    testCalendarOperations();
    cout << "Calendar operations (adding, moving, removing) test passed" << endl;

}