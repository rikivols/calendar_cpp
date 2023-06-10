#include "testDates.h"
#include "testConflict.h"
#include "testCalendarOperations.h"


int main() {
    testDateValid();
    testOperations();
    testConflictRecurring();
    testConflictMix();
    testLongEvents();
    testCalendarAdd();
}