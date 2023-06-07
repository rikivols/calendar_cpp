#include "CApplication.h"


CApplication::CApplication() : mLastEventId(1) {}


bool CApplication::handleImport() {
    CCalendarImporter importer;
    string filePath;

    while (true) {
        cout << "Do you want to import from a file or start with an empty calendar?" << endl;
        cout << "1 - import from file" << endl;
        cout << "2 - start with an empty calendar" << endl;

        int displayMode = getUserOption(2);

        if (displayMode == 1) {
            cout << "Select path to the file you want to import from: ";
            loadString(filePath);
            cout << endl;
            mCalendar = importer.importFromFile(filePath);
            return importer.wasSuccess();
        }
        else if (displayMode == 2) {
            return true;
        }
    }

}


void CApplication::displayMainMenu() {

    while (true) {
        cout << endl << "You're at the main menu of the calendar, what action do you want to choose?" << endl;
        cout << "1 - add event" << endl;
        cout << "2 - move event" << endl;
        cout << "3 - remove event" << endl;
        cout << "4 - find event" << endl;
        cout << "5 - display calendar" << endl;
        cout << "6 - export calendar" << endl;
        cout << "7 - end application" << endl;

        int option = getUserOption(7);
        cout << endl;

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
                break;
        }
    }
}


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

                int pageMode = getUserOption(3);

                if (pageMode == 3) return;

                if (pageMode == 1) {
                    calendarDisplayer[displayMode]->previousPage();
                }
                else if (pageMode == 2) {
                    calendarDisplayer[displayMode]->nextPage();
                }
            }
        }

        cout << endl;
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

    cout << "You're about to add an event, fill the fields below:" << endl;
    cout << "Enter event name: ";
    loadString(eventName);

    while (true) {
        cout << "Is your event recurring (happens every day)? (y/n): ";
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
            cout << "Invalid format, please try again." << endl;
        }
    }

    while (true) {
        cout << "You're about to enter a date and time of the start of the event:" << endl;
        startDate.loadDatetime();

        if (isRecurring) {
            cout << "Enter end time (recurring events don't have end date):" << endl;
            endTime.loadTime();

            if (startDate.getTime() == endTime) {
                cout << "Event can't have 0 minute duration, please enter dates again" << endl;
            }
            else {
                break;
            }
        } else {
            cout << "You're about to enter a date and time of the end of the event:" << endl;
            endDate.loadDatetime();

            if (startDate == endDate) {
                cout << "Event can't have 0 minute duration, please enter dates again" << endl<< endl;
            }
            else if (startDate >= endDate) {
                cout << "Start date can't come after end date, please enter dates again" << endl << endl;
            }
            else {
                break;
            }
        }
    }

    cout << "Enter event place: ";
    loadString(place);

    cout << "How many attendees does your event have (0-99): ";
    loadMultiString(attendees, "attendee", 99);

    cout << "How many tags does your event have (0-99): ";
    loadMultiString(tags, "tag", 99);

    cout << "Enter notes (optional): ";
    loadString(notes, true);

    bool addSuccess;

    if (isRecurring) {
        auto eventRecurring = CEventRecurring(mLastEventId, eventName, startDate, endTime, place, attendees, tags, notes);
        addSuccess = mCalendar.addEvent(eventRecurring);
    }
    else {
        auto eventSimple = CEventSimple(mLastEventId, eventName, startDate, endDate, place, attendees, tags, notes);
        addSuccess = mCalendar.addEvent(eventSimple);
    }

    if (addSuccess) {
        mLastEventId++;
    }
}

void CApplication::moveEvent() {
    cout << "Please select id of an event that you want to move: ";
    size_t eventId = loadNumber(1, 999999999);

    if (!mCalendar.getEvent(eventId)) {
        cout << "event doesn't exist" << endl;
        return;
    }

    cout << "Select by how many hours you want to move the event (-23, 23): " << endl;
    int hours = loadNumber(-23, 23);

    mCalendar.moveEvent(eventId, hours);
}

void CApplication::removeEvent() {
    cout << "Select id of an event that you want to remove: ";
    size_t eventId = loadNumber(1, 999999999);

    mCalendar.removeEvent(eventId);
}


void CApplication::findEvents() {

}

void CApplication::exportCalendar() {
    CEventExporter exporter(mCalendar.getEvents());
    exporter.exportToFile();
}
