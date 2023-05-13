#include "application.h"


int main() {
    cout << "Welcome to the calendar app!" << endl;
    Application application;
    application.handleImport();
    application.displayMainMenu();

    return 0;
}
