#include "CApplication.h"
#include "CHelpers.cpp"

CApplication::CApplication() : mLastEventId(1) {}

void CApplication::displayCalendar() {

    while (true) {
        cout << "Select calendar display mode:" << endl;
        cout << "1 - daily" << endl;
        cout << "2 - weekly" << endl;
        cout << "3 - monthly" << endl;
        cout << "4 - cancel" << endl;

        int displayMode = getUserOption(4);

        if (displayMode == 4) return;

        if (calendarDisplayer.find(displayMode) != calendarDisplayer.end()) {
            calendarDisplayer[displayMode]->setCalendar(mCalendar);
            calendarDisplayer[displayMode]->display();

            while (true) {
                cout << "Calendar view options:" << endl;
                cout << "1 - go to previous page" << endl;
                cout << "2 - go to the next page" << endl;
                cout << "3 - cancel" << endl;

                int pageMode = getUserOption(4);

                if (pageMode == 3) return;

                if (pageMode == 1) {
                    calendarDisplayer[displayMode]->previousPage();
                }
                else if (pageMode == 2) {
                    calendarDisplayer[displayMode]->nextPage();
                }
            }
        }
    }
}

void CApplication::displayMainMenu() {

    while (true) {
        cout << "You're at the main menu of the calendar, what action do you want to choose?" << endl;
        cout << "1 - add event" << endl;
        cout << "2 - move event" << endl;
        cout << "3 - remove event" << endl;
        cout << "4 - find event" << endl;
        cout << "5 - display calendar" << endl;
        cout << "6 - export calendar" << endl;
        cout << "7 - end application" << endl;

        int option = getUserOption(7);

        switch (option) {
            case 1:
                this->addEvent();
                break;
            case 2:
                this->moveEvent();
                break;
            case 3:
                this->removeEvent();
                break;
            case 4:
                this->findEvents();
                break;
            case 5:
                this->displayCalendar();
                break;
            case 6:
                this->exportCalendar();
                break;
            case 7:
                return;
            default:
                continue;
        }

    }


}

void CApplication::addEvent() {

    string eventName, option, place, notes;
    bool isRecurring;
    CDatetime startDate;
    CDatetime endDate;
    CTime endTime;
    vector<string> attendees;
    vector<string> tags;

    cout << "Please select event name:" << endl;
    loadString(eventName);

    cout << "Is your event recurring (happens every day)? (y/n)" << endl;
    while (true) {
        cin >> option;
        convertStringLowercase(option);
        if (option == "yes" || option == "y") {
            isRecurring = true;
            break;
        }
        else if (option == "n" || option == "no") {
            isRecurring = false;
            break;
        }
        else {
            cout << "Invalid format, please enter again";
        }
    }

    while (true) {
        cout << "Enter start datetime:" << endl;
        startDate.loadDatetime();

        if (isRecurring) {
            cout << "Enter end time (recurring events don't have end date):";
            endTime.loadTime();

            if (startDate.getTime() == endTime) {
                cout << "Event can't have 0 minute duration, please enter datetimes again" << endl;
            }
            else {
                break;
            }
        } else {
            cout << "Enter end datetime:" << endl;
            endDate.loadDatetime();

            if (startDate == endDate) {
                cout << "Event can't have 0 minute duration, please enter datetimes again" << endl;
            }
            else if (startDate >= endDate) {
                cout << "Start date can't come after end date, please enter datetimes again" << endl;
            }
            else {
                break;
            }
        }
    }

    cout << "Enter event place:" << endl;
    loadString(place);

    cout << "How many attendees does your event have:" << endl;
    loadMultiString(attendees, "attendee", 99);

    cout << "How many tags does your event have:" << endl;
    loadMultiString(tags, "tag", 99);

    cout << "Enter notes (optional):" << endl;
    loadString(notes);

    if (isRecurring) {
        mCalendar.addEvent(CEventRecurring(mLastEventId, eventName, startDate, endTime, place, attendees, tags, notes));
    }
    else {
        mCalendar.addEvent(CEventSimple(mLastEventId, eventName, startDate, endDate, place, attendees, tags, notes));
    }

    mLastEventId++;
}
