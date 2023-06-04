
#include "CEventExporter.h"


CEventExporter::CEventExporter(const map<size_t, shared_ptr<CEvent>> &events) : mEvents(events) {}

void CEventExporter::exportToFile() const {
    auto timeNow = getTimeNow();
    string filePath = "../assets/calendarFullExport_" + to_string(timeNow->tm_year) + "_" + to_string(timeNow->tm_mon)
            + "_" + to_string(timeNow->tm_mday) + "_" + to_string(timeNow->tm_hour) + "_" + to_string(timeNow->tm_min);
    ofstream exportFile(filePath, ios::out);

    if (!exportFile || !exportFile.is_open()) {
        cout << "Failed to open the provided file." << endl;
        return false;
    }

    string fileRow;
    int lineNum = 0;
    for (const auto &[id, event]: mEvents) {
        if (!exportFile || !exportFile.is_open()) {
            cout << "Failed to open the provided file, error occurred on line: " << lineNum << endl;
            return false;
        }
        event->exportEvent(fileRow);
        exportFile << fileRow;
        if (!exportFile.good()) {
            cout << "Failed to write to the file, error occurred on line: " << lineNum << endl;
            exportFile.close();
            return false;
        }
        lineNum++;
    }

    cout << "Successfully exported " << lineNum << " events to the file: " << filePath << endl;
    exportFile.close();

    return true;
}
