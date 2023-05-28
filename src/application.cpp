#include "application.h"
#include "helpers.cpp"

Application::Application() : lastEventId(0) {}

void Application::displayCalendar() {

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

void Application::displayMainMenu() {

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

void Application::addEvent() {

    string eventName, option, place, notes;
    bool isRecurring;
    Datetime startDate;
    Datetime endDate;
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

    cout << "Enter start datetime:" << endl;
    startDate.loadDatetime();

    if (isRecurring) {
        cout << "Enter end time (recurring events don't have end date):";
        endDate.loadDatetime(true);
    }
    else {
        cout << "Enter end datetime:" << endl;
        endDate.loadDatetime();
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
        mCalendar.addEvent(EventRecurring(mLastEventId, eventName, startDate, place, attendees, tags, notes));
    }
    else {
        mCalendar.addEvent(EventSimple(mLastEventId, eventName, startDate, endDate, place, attendees, tags, notes));
    }

    mLastEventId++;
}
