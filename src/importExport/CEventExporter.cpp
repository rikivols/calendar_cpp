
#include "CEventExporter.h"


CEventExporter::CEventExporter(const map<size_t, shared_ptr<CEvent>> &events) : mEvents(events) {}

bool CEventExporter::exportToFile(const string &filePath) {
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

    cout << "Successfully exported " << lineNum << " events." << endl;
    exportFile.close();

    return true;
}
