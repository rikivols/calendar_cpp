
#pragma once

#include <fstream>

#include "../CCalendar.h"
#include "../event/CEvent.h"
#include "../event/CEventRecurring.h"
#include "../event/CEventSimple.h"


/**
 * Class responsible for importing of the calendar from file.
 */
class CCalendarImporter {
public:

    CCalendarImporter();

    /**
     * Import the calendar from a CSV - like format. All event's properties are separated by the  ',' and array
     * properties are enclosed in the '[]'
     *
     * @param[in] filePath path of the file we want to import from
     * @return the imported calendar.
     */
    CCalendar importFromFile(const string &filePath);

    /**
     * If an error happens during the import, print it out and return an empty calendar.
     *
     * @param message message of the error to print
     * @param lineNum line where the error happened
     * @return Empty calendar.
     */
    [[nodiscard]] static CCalendar errorReturn(const string &message, size_t lineNum=0) ;

    /**
     * @return if import was successful
     */
    [[nodiscard]] bool wasSuccess() const;

private:
    /**
     * Check if the string of the event id's is correct, and if it's not a duplicate.
     *
     * Set the event id or save an error message.
     *
     * @param inp string to parse
     */
    void parseEventId(const string &inp);

    /**
     * Check if the string of the event string property is correct. Sets that property, checks if it's not empty.
     *
     * Set the event id or save an error message.
     *
     * @param inp string to parse
     * @param elementString element property to store the string to
     * @param allowEmpty if we want to allow an empty string (notes)
     */
    void parseString(const string &inp, string &elementString, bool allowEmpty=false);

    /**
     * Check if the given string can be parsed into the event's datetime and if it's valid.
     *
     * Set the event datetime or set an error message.
     *
     * @param inp string to parse
     * @param datetimeOutput element's datetime to store the parsed result to
     */
    void parseDatetime(const string &inp, CDatetime &datetimeOutput);

    /**
     * Check if the given string can be parsed into the event's time (end time for recurring events).
     *
     * Set the event time or set an error message.
     *
     * @param inp string to parse
     */
    void parseTime(const string &inp);

    /**
    * Check if the string of the event vector property is correct.
    *
    * Set the event's vector property or save an error message.
    *
    * @param inp string to parse
    * @param finalVec element vector to store the parsed info to
    */
    void parseVector(string &inp, vector<string> &finalVec);

    /**
     * Set error message if it's empty
     *
     * @param message message to set.
     */
    void setErrorMessage(const string &message);

    size_t mEventId;
    string mEventType, mName, mPlace, mNote, mErrorMessage;
    CDatetime mStart, mEnd;
    CTime mEndTime;
    vector<string> mAttendees, mTags;
    set<size_t> mUsedEventIds;
    bool isSuccess;
};
