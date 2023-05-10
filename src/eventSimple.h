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
#include "event.h"

class EventSimple: public Event {
public:
    EventSimple(size_t eventId, const Datetime &start, const Datetime &end, string place, const vector<string> &attendees,
                const set<string> &tags, const string &notes);

    [[nodiscard]] shared_ptr<Event> clone() const override;

    ostream &print(ostream &out) const override;

    void setDatetime(const Datetime & datetime) override;

    [[nodiscard]] bool isConflict(const Datetime & datetime) const override;

protected:
    size_t mEventId;
    Datetime mStart;
    Datetime mEnd;
    string mPlace;
    vector<string> mAttendees;
    set<string> mTags;
    string mNotes;
};
