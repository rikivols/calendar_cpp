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

string & loadString(string &loadedString, bool allowEmpty) {
    while (true) {
        if (allowEmpty) {
            cout << endl;
            cin.ignore();
            getline(cin, loadedString);
        }
        else {
            cin >> loadedString;
        }

        stripString(loadedString);

        if (cin.fail()) {
            cout << "Failed to load the text, please enter the value again: ";
        }
        else if (loadedString.empty() && !allowEmpty) {
            cout << "Can't have an empty string, please enter the value again: ";
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
        cout << "Select " << propertyName << " number " << i+1 << ": ";
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
            cout << "please try again: ";
        }
        else {
            break;
        }
    }

    return res;
}


string addZeroPadding(int num) {
    string res = to_string(num);

    if (res.size() == 1) {
        res = "0" + res;
    }

    return res;
}


ostream &printSeparator(ostream &out, int type) {
    out << endl;
    char c;
    switch (type) {
        case 0:
            c = '-';
            break;
        case 1:
            c = '=';
            break;
        default:
            c = ' ';
    }
    out << string(25, c);
    out << endl;

    return out;
}


ostream &printVector(ostream &out, const vector<string> &vec) {
    for (const auto &v: vec) {
        out << "* " << v << endl;
    }

    return out;
}

string stringifyDay(int year, int month, int day) {
    return addZeroPadding(year) + "." + addZeroPadding(month) + "." + addZeroPadding(day);
}


string &stripString(string & inp) {
    inp.erase(inp.begin(), find_if(inp.begin(), inp.end(), [](unsigned char ch) {  // remove prefix
        return !isspace(ch);
    }));

    inp.erase(find_if(inp.rbegin(), inp.rend(), [](unsigned char ch) {  // remove sufix
        return !isspace(ch);
    }).base(), inp.end());

    return inp;
}


string exportFormatVector(vector<string> &vec) {
    string res = "[";
    for (size_t i=0; i<vec.size(); i++) {
        res += vec[i];
        if (i != vec.size() - 1) {
            res += ",";
        }
    }
    res += "]";

    return res;
}


tm *getTimeNow() {
    time_t cTime = time(nullptr);
    return localtime(&cTime);
}
