#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void deleteSchedule()
{
    string searchID;
    char confirm;

    while (true)
    {
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

        string line;
        string deleteLine;
        bool found = false;

        // Search for the schedule
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

            // Only search current publisher's schedule
            if (s.scheduleID == searchID && s.publisherID == currentID)
            {
                found = true;
                deleteLine = line;

                cout << "\n----------------------------------------\n";
                cout << "Schedule found:\n";
                cout << "Schedule ID : " << s.scheduleID << endl;
                cout << "Day         : " << s.day << endl;
                cout << "Time        : " << s.startTime
                     << " - " << s.endTime << endl;
                cout << "----------------------------------------\n";

                // Ask for confirmation
                do
                {
                    cout << "\nAre you sure you want to delete this schedule? (Yes(y)/No(n))"
                         << endl;
                    cout << "Enter your choice: ";
                    cin >> confirm;

                    if (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n')
                    {
                        cout << "Please enter y or n.\n";
                    }

                } while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');

                break;
            }
        }

        file.close();

        // Schedule not found
        if (!found)
        {
            cout << "\nSchedule ID not found in your schedule.\n";
            continue;
        }

        // Publisher chooses NOT to delete
        if (confirm == 'N' || confirm == 'n')
        {
            cout << "\nSchedule was not deleted.\n";
            continue;
        }

        // Publisher chooses to delete
        if (confirm == 'Y' || confirm == 'y')
        {
            ifstream originalFile("Schedule.txt");
            ofstream temp("Schedule_temp.txt");

            while (getline(originalFile, line))
            {
                if (line != deleteLine)
                {
                    temp << line << endl;
                }
            }

            originalFile.close();
            temp.close();

            remove("Schedule.txt");
            rename("Schedule_temp.txt", "Schedule.txt");

            cout << "\nSchedule deleted successfully.\n";

            system("pause");
            return;
        }
    }
}
