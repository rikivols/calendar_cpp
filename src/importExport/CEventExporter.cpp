
#include "CEventExporter.h"


CEventExporter::CEventExporter(const vector<shared_ptr<CEvent>> &events): mEvents(events) {
    sort(mEvents.begin(), mEvents.end(), CEvent::sortEventsById);
}

void CEventExporter::exportToFile(const string &nameOfFile) const {
    auto timeNow = getTimeNow();
    string filePath = "assets/" + nameOfFile + "_" + to_string(timeNow->tm_year + 1900) + "_" + to_string(timeNow->tm_mon + 1)
            + "_" + to_string(timeNow->tm_mday) + "_" + to_string(timeNow->tm_hour) + "_" + to_string(timeNow->tm_min)
            + "_" + to_string(timeNow->tm_sec) + ".txt";
    ofstream exportFile(filePath, ios::out);

    if (!exportFile || !exportFile.is_open()) {
        cout << "Failed to open the provided file." << endl;
        return;
    }

    string fileRow;
    int lineNum = 0;
    for (const auto &event: mEvents) {
        if (!exportFile || !exportFile.is_open()) {
            cout << "Failed to open the provided file, error occurred on line: " << lineNum << endl;
            return;
        }
        event->exportEvent(fileRow);
        exportFile << fileRow << endl;
        if (!exportFile.good()) {
            cout << "Failed to write to the file, error occurred on line: " << lineNum << endl;
            exportFile.close();
            return;
        }
        lineNum++;
    }

    cout << "Successfully exported " << lineNum << " events to the file: " << filePath << endl;
    exportFile.close();
}
