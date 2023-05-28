#include "helpers.h"

int getUserOption(int maxChoice) {
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

void loadString(string &loadedString) {
    while (true) {
        cin >> loadedString;

        if (cin.fail()) {
            cout << "Failed to load the text, please try again" << endl;
        }
        else if (loadedString.empty()) {
            cout << "text can't be empty, please select again" << endl;
        }
        else {
            break;
        }
    }
}

void convertStringLowercase(string &toConv) {
    for (char & c : toConv) {
        c = (char)tolower(c);
    }
}


int loadNumber(int minNum, int maxNum) {
    int res;

    while (true) {
        cin >> res;
        if (cin.fail()) {
            cout << "Failed to load the number, please try again" << endl;
        }
        else if (res < minNum || res > maxNum) {
            cout << "Selected number is out of range, acceptable values are: [" << minNum << "..." << maxNum << "]" << endl;
        }
        else {
            break;
        }
    }

    return res;
}