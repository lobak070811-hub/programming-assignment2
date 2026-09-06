#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void deleteSchedule()
{
    string searchID;

    cout << "\n========================================\n";
    cout << "           DELETE SCHEDULE\n";
    cout << "========================================\n";

    cout << "Publisher ID : " << currentID << endl;

    cout << "\nEnter Schedule ID to delete: ";
    cin >> searchID;

    ifstream file("Schedule.txt");

    if (!file)
    {
        cout << "\nNo schedule file found.\n";
        return;
    }

    ofstream temp("Schedule_temp.txt");

    string line;

    bool found = false;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        Schedule s;

        getline(ss, s.scheduleID, '|');
        getline(ss, s.publisherID, '|');
        getline(ss, s.day, '|');
        getline(ss, s.startTime, '|');
        getline(ss, s.endTime);

        // Only delete current publisher's schedule
        if (s.scheduleID == searchID &&
            s.publisherID == currentID)
        {
            found = true;

            cout << "\nSchedule found:";
            cout << "\nSchedule ID : " << s.scheduleID;
            cout << "\nDay         : " << s.day;
            cout << "\nTime        : "
                 << s.startTime << " - "
                 << s.endTime << endl;

            cout << "\nSchedule deleted successfully.\n";

            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    if (!found)
    {
        cout << "\nSchedule ID not found in your schedule.\n";
        remove("Schedule_temp.txt");
        return;
    }

    remove("Schedule.txt");

    rename("Schedule_temp.txt", "Schedule.txt");
}
