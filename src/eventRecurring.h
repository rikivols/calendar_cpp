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
#include <set>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <memory>
using namespace std;

#include "datetime.h"
#include "eventSimple.h"

class EventRecurring: public EventSimple {
public:
    EventRecurring(size_t eventId, const Datetime &start, const Datetime &end, const string &place, const vector<string> &attendees,
                const set<string> &tags, const string &notes);

    [[nodiscard]] shared_ptr<Event> clone() const override;

    ostream &print(ostream &out) const override;

    bool isConflict(const Datetime & datetime) const override;
};
