#include "../utils/CDatetime.h"


void testDateValid() {
    CDatetime datetime;
    assert(datetime.isValidDate() == false);

    CDatetime datetime2(2023, 5, 4, 15, 30);
    assert(datetime2.isValidDate() == true);

    // test edge dates
    CDatetime datetime3(2023, 6, 30, 15, 30);
    assert(datetime3.isValidDate() == true);

    CDatetime datetime4(2023, 6, 31, 15, 30);
    assert(datetime4.isValidDate() == false);

    // test out of bounds
    CDatetime datetime5(2023, 6, 31, 15, 60);
    assert(datetime5.isValidDate() == false);

    CDatetime datetime6(2023, 6, 31, 24, 0);
    assert(datetime6.isValidDate() == false);

    CDatetime datetime7(2023, 13, 29, 15, 59);
    assert(datetime7.isValidDate() == false);

    CDatetime datetime8(1800, 12, 29, 15, 59);
    assert(datetime8.isValidDate() == false);

    // test leap day
    CDatetime datetime9(2020, 12, 29, 15, 59);
    assert(datetime9.isValidDate() == true);

    CDatetime datetime10(2021, 12, 29, 15, 59);
    assert(datetime10.isValidDate() == false);
}


void testOperations() {
    CDatetime datetime1(2023, 5, 4, 15, 30);
    assert(datetime1 + 5 == CDatetime(2023, 5, 4, 15, 35));
    assert(datetime1 == CDatetime(2023, 5, 4, 15, 30));

    assert(datetime1 + 1440 == CDatetime(2023, 5, 5, 15, 30));
    assert(datetime1 + 43800 == CDatetime(2023, 6, 4, 15, 30));
    assert(datetime1 + 525600 == CDatetime(2024, 5, 4, 15, 30));
    assert(datetime1 + 9 * 60 == CDatetime(2023, 5, 5, 0, 30));

    assert(datetime1 - 5 == CDatetime(2024, 5, 4, 15, 25));
    assert(datetime1 - 60 == CDatetime(2024, 5, 4, 14, 30));

    assert((datetime1 += 10) == CDatetime(2023, 5, 4, 15, 40));
    assert(datetime1 == CDatetime(2023, 5, 4, 15, 40));
}


int main(void) {
    testDateValid();
    testOperations();

}