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

#include "datetime.h"

using namespace std;

class Event {
public:
    virtual ~Event() noexcept = default;

    virtual shared_ptr<Event> clone() const = 0;

    virtual ostream &print(ostream &out) const = 0;

    virtual void setDatetime(const Datetime & datetime) = 0;

    virtual bool isConflict(const Datetime & datetime) const = 0;

};

std::ostream & operator<<(std::ostream & out, const Event & self);
