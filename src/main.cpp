#include "CApplication.h"


int main() {
    cout << "Welcome to the calendar app!" << endl;
    CApplication application;
    application.handleImport();
    application.displayMainMenu();

    return 0;
}
