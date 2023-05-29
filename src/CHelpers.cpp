#include "CHelpers.h"

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

string & loadString(string &loadedString, bool emptyCheck) {
    while (true) {
        cin >> loadedString;

        if (cin.fail()) {
            cout << "Failed to load the text, please try again" << endl;
        }
        else if (emptyCheck && loadedString.empty()) {
            cout << "text can't be empty, please select again" << endl;
        }
        else {
            return loadedString;
        }
    }
}

vector<string> &loadMultiString(vector<string> &storeVec, const string &propertyName, int maxNum) {
    string value;


    int numberOfValues = loadNumber(0, maxNum);

    for (size_t i=0; i<numberOfValues; i++) {
        cout << "Select " << propertyName << " number " << i+1 << ":" << endl;
        storeVec.push_back(loadString(value));
    }

    return storeVec;
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