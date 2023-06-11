
#include "CHelpers.h"


int getUserOption(int maxChoice) {

    cout << "Pick an option (1-" << maxChoice << "): ";
    string optionStr;
    cin >> optionStr;
    cout << endl;

    int option = convertStringToInt(optionStr);

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


string &loadString(string &loadedString, bool allowEmpty) {
    while (true) {
        getline(cin >> ws, loadedString);

        stripString(loadedString);

        if (cin.fail()) {
            cout << "Failed to load the text" << endl;
            loadedString = "";
            cin.clear();
            cin.sync();
            return loadedString;
        }
        else if (loadedString.empty() && !allowEmpty) {
            loadedString = "";
            cin.clear();
            cin.sync();
            continue;
        }
        else {
            if (allowEmpty && loadedString == "default") {
                loadedString = "";
                return loadedString;
            }
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

    cout << endl;

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
            cout << "please enter again: ";
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


ostream &printSeparator(ostream &out, char separator) {
    out << endl;
    out << string(35, separator);
    out << endl;

    return out;
}


ostream &printVector(ostream &out, const vector<string> &vec) {
    for (const auto &v: vec) {
        out << "| * " << v << endl;
    }

    return out;
}


string &stripString(string & inp) {
    inp.erase(inp.begin(), find_if(inp.begin(), inp.end(), [](unsigned char ch) {  // remove prefix
        return !isspace(ch);
    }));

    inp.erase(find_if(inp.rbegin(), inp.rend(), [](unsigned char ch) {  // remove suffix
        return !isspace(ch);
    }).base(), inp.end());

    return inp;
}


string exportFormatVector(const vector<string> &vec) {
    string res = "[";
    for (size_t i=0; i<vec.size(); i++) {
        res += vec[i];
        if (i != vec.size() - 1) {
            res += ";";
        }
    }
    res += "]";

    return res;
}


tm *getTimeNow() {
    time_t cTime = time(nullptr);
    return localtime(&cTime);
}


void splitString(vector<string> &result, const string &line, char separator) {
    size_t start = 0;
    string element;

    for (size_t i = 0; i <= line.size(); i++) {
        element = "";
        if (line[i] == separator || i == line.size()) {
            // append every word to the string once we have the separator
            element.append(line, start, i - start);
            result.push_back(stripString(element));
            start = i + 1;
        }
    }
}


int convertStringToInt(const string &inp) {
    int res;

    try {
        res = stoi(inp);
    }
    catch (...) {
        res = -1;
    }

    return res;
}


bool loadYesNo(const string &message) {
    string option;
    while (true) {
        cout << message << "(y/n): ";
        loadString(option);
        convertStringLowercase(option);
        if (option == "yes" || option == "y") {
            return true;
        }
        else if (option == "n" || option == "no") {
            return false;
        }
        else {
            cout << "Invalid format, please try again." << endl;
        }
    }
}


bool isInVector(const vector<string> &vec1, const vector<string> &vec2) {
    for (const auto &v1: vec1) {
        bool wasMatch = false;
        for (const auto &v2: vec2) {
            if (v1 == v2) {
                wasMatch = true;
            }
        }

        if (!wasMatch) {
            return false;
        }
    }

    return true;
}
