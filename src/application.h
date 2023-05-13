
#include "calendar.h"
#include "displayCalendar.h"

class Application {
public:
    Application();

    /**
     * Asks user whether to initialize an empty calendar or import it from a file
     */
    void handleImport();

    /**
     * Starts the main loop of the calendar application. Prompts user with the main menu. Main menu has options
     * to add, move, remove, display events.
     */
    void displayMainMenu();

    /**
     * Prompts user to add
     */
    void addEvent();

    void moveEvent();

    void removeEvent();

    void findEvents();

    void displayCalendar();

    void exportCalendar();

private:
    Calendar mCalendar;
    size_t lastEventId;
};

