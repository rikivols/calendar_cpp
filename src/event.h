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
#include <set>

#include "datetime.h"

using namespace std;

class Event {
public:
    virtual ~Event() noexcept = default;

    [[nodiscard]] virtual shared_ptr<Event> clone() const = 0;

    virtual ostream &print(ostream &out) const = 0;

    virtual void setStart(const Datetime &datetime) = 0;

    virtual void setEnd(const Datetime &datetime) = 0;

    virtual size_t getId() const = 0;

    [[nodiscard]] virtual bool isConflict(const shared_ptr<Event> &event, size_t offset) const = 0;
};

std::ostream & operator<<(std::ostream & out, const Event & self);
