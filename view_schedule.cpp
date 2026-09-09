#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void viewSchedule()
{
    ifstream file("Schedule.txt");

    if (!file)
    {
        cout << "\nNo schedule available.\n";
        
        system("pause");
        return;
    }

    string line;

    bool found = false;

    cout << "\n========================================\n";
    cout << "             MY SCHEDULE\n";
    cout << "========================================\n";

    cout << "Publisher ID : " << currentID << "\n";

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

        if (s.publisherID == currentID)
        {
            found = true;

            cout << "\nSchedule ID : " << s.scheduleID;
            cout << "\nDay         : " << s.day;
            cout << "\nTime        : "
                 << s.startTime << " - "
                 << s.endTime;
            cout << "\n----------------------------------------";
        }
    }

    file.close();

    if (!found)
    {
        cout << "\n\nYou do not have any schedule yet.\n";
        
        system("pause");
        return;
    }

    cout << endl;
    
    system("pause");
}
