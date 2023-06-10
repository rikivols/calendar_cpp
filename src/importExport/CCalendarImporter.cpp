#include "CCalendarImporter.h"


CCalendarImporter::CCalendarImporter(): mEventId(0), isSuccess(false) {}


CCalendar CCalendarImporter::importFromFile(const string &filePath) {
    size_t lineNum = 1;
    string fileRow, curElementString;
    vector<string> lineElements;
    CCalendar finalCalendar;

    ifstream readFile(filePath);

    if (readFile.is_open()) {
        while (getline(readFile, fileRow)) {
            if (!readFile.good()) {
                return errorReturn("Failed to read a line from file", lineNum);
            }

            stripString(fileRow);
            if (fileRow.empty()) {
                lineNum++;
                continue;
            }

            lineElements.clear();
            splitString(lineElements, fileRow, ',');

            if (lineElements.size() != 9) {
                return errorReturn("Wrong number of elements");
            }

            // event id
            parseEventId(lineElements[0]);

            // event type
            parseString(lineElements[1], mEventType);
            if (mEventType != "sim" && mEventType != "rec") {
                mErrorMessage = "Event type must be 'sim' or 'rec'";
            }

            // event name
            parseString(lineElements[2], mName);

            // datetime
            parseDatetime(lineElements[3], mStart);

            if (mEventType == "sim") {
                parseDatetime(lineElements[4], mEnd);
                if (mStart >= mEnd) {
                    mErrorMessage = "Calendar event can't have 0 or negative duration";
                }
            } else {
                parseTime(lineElements[4]);
                if (mEndTime == mStart.getTime()) {
                    mErrorMessage = "Calendar event can't have 0 duration";
                }
            }

            // place
            parseString(lineElements[5], mPlace);

            // attendees
            parseVector(lineElements[6], mAttendees);

            // tags
            parseVector(lineElements[7], mTags);

            // note
            parseString(lineElements[8], mNote, true);

            // error during parsing
            if (!mErrorMessage.empty()) {
                return errorReturn(mErrorMessage, lineNum);
            }

            bool addSuccess;

            if (mEventType == "sim") {
                auto eventSimple = CEventSimple(mEventId, mName, mStart, mEnd, mPlace, mAttendees, mTags, mNote);
                addSuccess = finalCalendar.addEvent(eventSimple, true);
            }
            else if (mEventType == "rec") {
                auto eventRecurring = CEventRecurring(mEventId, mName, mStart, mEndTime, mPlace, mAttendees, mTags, mNote);
                addSuccess = finalCalendar.addEvent(eventRecurring, true);
            }
            else {
                return errorReturn("Event type must be 'sim' or 'rec'", lineNum);
            }

            if (!addSuccess) {
                return errorReturn("Event already exists at that time", lineNum);
            }

            mAttendees.clear();
            mTags.clear();

            lineNum++;
        }
    }
    else {
        return errorReturn("Unable to open the file");
    }

    readFile.close();
    cout << "Calendar was successfully imported. Number of events: " << lineNum - 1 << endl;
    isSuccess = true;

    return finalCalendar;
}


CCalendar CCalendarImporter::errorReturn(const string &message, size_t lineNum) {
    cout << "IMPORT FAIL: ";
    if (lineNum) {
        cout << "on line: " << lineNum << " ";
    }
    cout << message << endl;
    return CCalendar();
}


void CCalendarImporter::parseEventId(const string &inp) {
    long long eventId;

    try {
        eventId = stoi(inp);
    }
    catch (...) {
        setErrorMessage("Event's event id in wrong format");
        return;
    }

    if (eventId < 1) {
        setErrorMessage("Event id can't be 0 or negative");
        return;
    }

    if (eventId > SIZE_MAX) {
        setErrorMessage("Event id is too big, max value: " + to_string(SIZE_MAX));
        return;
    }

    if (mUsedEventIds.find(eventId) != mUsedEventIds.end()) {
        setErrorMessage("Event id already exists");
        return;
    }

    mEventId = eventId;
}

void CCalendarImporter::parseString(const string &inp, string &elementString, bool allowEmpty) {
    if (!allowEmpty && inp.empty()) {
        setErrorMessage("Your string element can't be empty");
        return;
    }
    elementString = inp;
}


void CCalendarImporter::parseDatetime(const string &inp, CDatetime &datetimeOutput) {
    vector<string> dateTime;
    vector<string> date;
    vector<string> time;
    int year, month, day, hour, minute;

    string dateErrorMessage = "Given datetime doesn't match the format: YYYY.MM.DD HH:MM";
    splitString(dateTime, inp, ' ');

    if (dateTime.size() != 2) {
        setErrorMessage(dateErrorMessage);
        return;
    }

    splitString(date, dateTime[0], '.');
    splitString(time, dateTime[1], ':');

    if (date.size() != 3 || time.size() != 2) {
        setErrorMessage(dateErrorMessage);
        return;
    }

    year = convertStringToInt(date[0]);
    month = convertStringToInt(date[1]);
    day = convertStringToInt(date[2]);
    hour = convertStringToInt(time[0]);
    minute = convertStringToInt(time[1]);

    CDatetime finalDatetime(year, month, day, hour, minute);
    if (!finalDatetime.isValidDate()) {
        setErrorMessage("Invalid datetime");
    }
    datetimeOutput = finalDatetime;
}


void CCalendarImporter::parseTime(const string &inp) {
    vector<string> time;
    int hour, minute;

    string timeErrorMessage = "Given time doesn't match the format: HH:MM";
    splitString(time, inp, ':');

    if (time.size() != 2) {
        setErrorMessage(timeErrorMessage);
        return;
    }

    hour = convertStringToInt(time[0]);
    minute = convertStringToInt(time[1]);

    CTime finalTime(hour, minute);
    if (!finalTime.isValidTime()) {
        setErrorMessage("Invalid time");
    }
    mEndTime = finalTime;
}


void CCalendarImporter::parseVector(string &inp, vector<string> &finalVec) {
    if (inp.size() < 2 || inp[0] != '[' || inp[inp.size()-1] != ']') {
        setErrorMessage("Array type attributes must be enclosed in '[' and ']' characters");
        return;
    }

    inp.erase(0, 1);
    inp.pop_back();

    if (inp.empty()) {
        return;
    }

    splitString(finalVec, inp, ';');

    for (auto &v: finalVec) {
        if (stripString(v).empty()) {
            setErrorMessage("Array element can't be empty");
        }
    }
}
