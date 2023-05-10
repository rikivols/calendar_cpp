#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <memory>

class Datetime {
public:
    Datetime(size_t year, size_t month, size_t day, size_t hour, size_t minute): mYear(year), mMonth(month), mDay(day),
                                                                                 mHour(hour), mMinute(minute) {};

    bool isValid() {};

    bool isInRange(const Datetime &from, const Datetime &to) {};

private:
    size_t mYear;
    size_t mMonth;
    size_t mDay;
    size_t mHour;
    size_t mMinute;
};
