
#include "CApplication.h"


int main() {
    cout << "--------------------------------" << endl;
    cout << "| Welcome to the calendar app! |" << endl;
    cout << "--------------------------------" << endl;
    CApplication application;
    bool wasSuccess = application.handleImport();
    if (wasSuccess) {
        application.displayMainMenu();
    }
    cout << "goodbye" << endl;

    return 0;
}
