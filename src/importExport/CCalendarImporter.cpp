#include "CCalendarImporter.h"


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

            lineElements.clear();
            splitString(lineElements, fileRow, ',');

            if (lineElements.size() != 9) {
                return errorReturn("Wrong number of elements");
            }

            for (size_t i=0; i<lineElements.size(); i++) {
                curElementString = stripString(lineElements[i]);

                switch (i) {
                    case 0:
                        parseEventId(curElementString);
                        break;
                    case 1: {
                        parseString(curElementString, mEventType);
                        if (mEventType != "sim" || mEventType != "rec") {
                            mErrorMessage = "Event type must be 'sim' or 'rec'";
                        }
                        break;
                    }
                    case 2:
                        parseString(curElementString, mName);
                        break;
                    case 3:
                        parseDatetime(curElementString, mStart);
                        break;
                    case 4: {
                        if (mEventType == "sim") {
                            parseDatetime(curElementString, mEnd);
                        } else {
                            parseTime(curElementString);
                        }
                        break;
                    }
                    case 5:
                        parseString(curElementString, mPlace);
                        break;
                    case 6:
                        parseVector(curElementString, mAttendees);
                        break;
                    case 7:
                        parseVector(curElementString, mTags);
                        break;
                    case 8:
                        parseString(curElementString, mNote, true);
                        break;
                    default:
                        throw logic_error("This shouldn't be possible, call the cops");
                }

                if (!mErrorMessage.empty()) {
                    return errorReturn(mErrorMessage, lineNum);
                }
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
                return errorReturn("Failed to add a new event", lineNum);
            }

            lineNum++;
        }
    }
    else {
        return errorReturn("Unable to open the file");
    }

    readFile.close();

    return finalCalendar;
}


CCalendar CCalendarImporter::errorReturn(const string &message, size_t lineNum) {
    cout << "IMPORT FAIL: ";
    if (lineNum) {
        cout << "on line: " << lineNum << " ";
    }
    cout << message << ", importing an empty calendar instead" << endl;
    return CCalendar();
}


void CCalendarImporter::parseEventId(const string &inp) {
    long long eventId;

    try {
        eventId = stoi(inp);
    }
    catch (...) {
        mErrorMessage = "Event's event id in wrong format";
        return;
    }

    if (eventId < 1) {
        mErrorMessage = "Event id can't be 0 or negative";
        return;
    }

    if (eventId > SIZE_MAX) {
        mErrorMessage = "Event id is too big, max value: " + to_string(SIZE_MAX);
        return;
    }

    if (mUsedEventIds.find(eventId) != mUsedEventIds.end()) {
        mErrorMessage = "Event id already exists";
        return;
    }

    mEventId = eventId;
}

void CCalendarImporter::parseString(const string &inp, string &elementString, bool allowEmpty) {
    if (!allowEmpty && inp.empty()) {
        mErrorMessage = "Your string element can't be empty";
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
        mErrorMessage = dateErrorMessage;
        return;
    }

    splitString(date, dateTime[0], '.');
    splitString(time, dateTime[1], ':');

    if (date.size() != 3 || time.size() != 2) {
        mErrorMessage = dateErrorMessage;
        return;
    }

    year = convertStringToInt(date[0]);
    month = convertStringToInt(date[1]);
    day = convertStringToInt(date[2]);
    hour = convertStringToInt(time[0]);
    minute = convertStringToInt(time[1]);

    CDatetime finalDatetime(year, month, day, hour, minute);
    if (!finalDatetime.isValidDate()) {
        mErrorMessage = "Invalid datetime";
    }
    datetimeOutput = finalDatetime;
}


void CCalendarImporter::parseTime(const string &inp) {
    vector<string> time;
    int hour, minute;

    string timeErrorMessage = "Given time doesn't match the format: HH:MM";
    splitString(time, inp, ':');

    if (time.size() != 2) {
        mErrorMessage = timeErrorMessage;
        return;
    }

    hour = convertStringToInt(time[0]);
    minute = convertStringToInt(time[1]);

    CTime finalTime(hour, minute);
    if (!finalTime.isValidTime()) {
        mErrorMessage = "Invalid time";
    }
    mEndTime = finalTime;
}


void CCalendarImporter::parseVector(string &inp, vector<string> &finalVec) {
    if (inp.size() < 2 || inp[0] != '[' || inp[inp.size()-1] != ']') {
        mErrorMessage = "Array type attributes must be enclosed in '[' and ']' characters";
        return;
    }

    inp.erase(0, 1);
    inp.pop_back();

    splitString(finalVec, inp, ';');

    for (auto &v: finalVec) {
        if (stripString(v).empty()) {
            mErrorMessage = "Array element can't be empty";
        }
    }
}
