#include "CApplication.h"


CApplication::CApplication() : mLastEventId(1) {
    calendarDisplayer[1] = CDisplayDaily().clone();
    calendarDisplayer[2] = CDisplayWeekly().clone();
    calendarDisplayer[3] = CDisplayMonthly().clone();
}


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
        cout << "7 - get event by id" << endl;
        cout << "8 - end application" << endl;

        int option = getUserOption(8);
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
                this->getEventById();
                break;
            case 8:
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
            calendarDisplayer[displayMode]->refreshCurrentPage();
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

    isRecurring = loadYesNo("Is your event recurring (happens every day)?");

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
    bool wereEventsFound, continueSearching, isAnd=true;
    string name, place, isAndRaw;
    CDatetime start = CDatetime(), end = CDatetime();
    vector<string> attendees, tags;
    int numOfEntries = 0;

    while (true) {
        cout << endl << "By what criteria do you want to search in the calendar?" << endl;
        cout << "1 - search by event name (exact match)" << endl;
        cout << "2 - search by event start date time (from)" << endl;
        cout << "3 - search by event end date time (to)" << endl;
        cout << "4 - search by event place (exact match)" << endl;
        cout << "5 - search by event attendees (event contains)" << endl;
        cout << "6 - search by event tags (event contains)" << endl;
        cout << "7 - finish search entry (you'll enter AND or OR clause later)" << endl;

        int selectedOption = getUserOption(7);

        switch(selectedOption) {
            case 1:
                cout << "Select event name: ";
                loadString(name);
                break;
            case 2:
                cout << "You're selecting event start datetime:" << endl;
                start.loadDatetime();
                break;
            case 3:
                cout << "You're selecting event end datetime:" << endl;
                end.loadDatetime();
                break;
            case 4:
                cout << "Select event place: " << endl;
                loadString(place);
                break;
            case 5:
                cout << "How many attendees do you want to enter? (0-99): ";
                loadMultiString(attendees, "attendee", 99);
                break;
            case 6:
                cout << "How many tags do you want to enter? (0-99): ";
                loadMultiString(tags, "tag", 99);
                break;
            default:
                break;
        }

        if (selectedOption == 7) {
            break;
        }
        numOfEntries++;

        continueSearching = loadYesNo("Do you want to add more search filters?");

        if (!continueSearching) {
            break;
        }
    }

    if (numOfEntries > 1) {
        while (true) {
            cout << "Do you want to search by AND or OR clause? (and/or): ";
            loadString(isAndRaw);
            convertStringLowercase(isAndRaw);

            if (isAndRaw == "and") {
                isAnd = true;
                break;
            } else if (isAndRaw == "or") {
                isAnd = false;
                break;
            } else {
                cout << "Your entry has to be 'and' or 'or', please try again." << endl;
            }
        }
    }

    CCalendarFinder finder(mCalendar, isAnd, name, start, end, place, attendees, tags);
    wereEventsFound = finder.findEvents();

    if (wereEventsFound) {
        cout << "Do you want to display the events or export them?" << endl;
        cout << "1 - display events" << endl;
        cout << "2 - export events" << endl;
        cout << "3 - cancel" << endl;

        int userOption = getUserOption(3);

        if (userOption == 1) {
            finder.printEvents();
        }
        if (userOption == 2) {
            finder.exportEvents();
        }
    }
}

void CApplication::exportCalendar() {
    CEventExporter exporter(mCalendar.getSortedEvents(nullptr, true));
    exporter.exportToFile("calendarFullExport");
}


void CApplication::getEventById() {
    cout << "Select id of an event you want to display: ";
    size_t eventId = loadNumber(1, 999999999);

    auto event = mCalendar.getEvent(eventId);

    if (event) {
        cout << *event;
    }
    else {
        cout << "Selected event doesn't exist" << endl;
    }
}
