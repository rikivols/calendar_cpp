#include "application.h"
#include "displayDaily.h"
#include "displayWeekly.h"
#include "displayMonthly.h"

Application::Application(): lastEventId(0) {}

void Application::displayCalendar() {

    map<int, shared_ptr<DisplayCalendar>> calendarDisplayer = {
            {1, make_shared<DisplayDaily>(mCalendar)}, {2, make_shared<DisplayWeekly>(mCalendar)},
            {3, make_shared<DisplayMonthly>(mCalendar)}
    };
    while (true) {
        cout << "Select calendar display mode:" << endl;
        cout << "1 - daily" << endl;
        cout << "2 - weekly" << endl;
        cout << "3 - monthly" << endl;
        cout << "4 - cancel" << endl;

        int displayMode = 0;
        cin >> displayMode;

        if (displayMode == 4) return;

        if (calendarDisplayer.find(displayMode) != calendarDisplayer.end()) {
            calendarDisplayer[displayMode]->display();

            cout << "Calendar view options:" << endl;
            cout << "1 - go to previous page" << endl;
            cout << "2 - go to the next page" << endl;
            cout << "3 - cancel" << endl;

            int pageMode = 0;
            cin >> pageMode;

            if (pageMode == 3) return;

            if (pageMode == 1) {
                calendarDisplayer[displayMode]->previousPage();
            }
            else if (pageMode == 2) {
                calendarDisplayer[displayMode]->nextPage();
            }
            else {
                cout << "Invalid display mode selected, please pick from options: {1, 2, 3}" << endl;
            }
        }
        else {
            cout << "Invalid display mode selected, please pick from options: {1, 2, 3, 4}" << endl;
        }
    }
}
