
#pragma once

#include <fstream>

#include "../CCalendar.h"
#include "../event/CEvent.h"
#include "../event/CEventRecurring.h"
#include "../event/CEventSimple.h"


/**
 * Class responsible for importing of the calendar.
 */
class CCalendarImporter {
public:

    CCalendarImporter();

    /**
     * Import the calendar from a CSV - like format
     *
     * @param[in] filePath path of the file we want to import from
     * @return true = import was successful
     *         false = import failed, display the reason
     */
    CCalendar importFromFile(const string &filePath);

    [[nodiscard]] static CCalendar errorReturn(const string &message, size_t lineNum=0) ;

    void parseEventId(const string &inp);

    void parseString(const string &inp, string &elementString, bool allowEmpty=false);

    void parseDatetime(const string &inp, CDatetime &datetimeOutput);

    void parseTime(const string &inp);

    void parseVector(string &inp, vector<string> &finalVec);

    bool wasSuccess() const {
        return isSuccess;
    }

private:
    size_t mEventId;
    string mEventType, mName, mPlace, mNote, mErrorMessage;
    CDatetime mStart, mEnd;
    CTime mEndTime;
    vector<string> mAttendees, mTags;
    set<size_t> mUsedEventIds;
    bool isSuccess;
};
