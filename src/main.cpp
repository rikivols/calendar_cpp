#include "CApplication.h"


int main() {
    cout << "--------------------------------" << endl;
    cout << "| Welcome to the calendar app! |" << endl;
    cout << "--------------------------------" << endl;
    CApplication application;
    application.handleImport();
    application.displayMainMenu();

    return 0;
}
