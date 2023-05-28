#include "application.h"

Application::Application() : lastEventId(0) {}

void Application::displayCalendar() {

    while (true) {
        cout << "Select calendar display mode:" << endl;
        cout << "1 - daily" << endl;
        cout << "2 - weekly" << endl;
        cout << "3 - monthly" << endl;
        cout << "4 - cancel" << endl;

        int displayMode = this->getUserOption(4);

        if (displayMode == 4) return;

        if (calendarDisplayer.find(displayMode) != calendarDisplayer.end()) {
            calendarDisplayer[displayMode]->setCalendar(mCalendar);
            calendarDisplayer[displayMode]->display();

            while (true) {
                cout << "Calendar view options:" << endl;
                cout << "1 - go to previous page" << endl;
                cout << "2 - go to the next page" << endl;
                cout << "3 - cancel" << endl;

                int pageMode = this->getUserOption(4);

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

        int option = this->getUserOption(7);

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

int Application::getUserOption(int maxChoice) {
    int option = -1;
    cin >> option;

    if (option < 1 || option > maxChoice) {
        cout << "Invalid option selected, please pick from options: {";
        for (int i=1; i<=maxChoice; i++) {
            cout << i;
            if (i != maxChoice) {
                cout << ", ";
            }
        }
        cout << "}\n" << endl;

        return -1;
    }

    return option;
}
