#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool validTime(string time);
bool scheduleOverlap(string day, string startTime, string endTime);

string defaultScheduleID();
string selectDay();
int timeToMinutes(string time);
 
void addSchedule()
{
    Schedule s;

    cout << "\n========================================\n";
    cout << "             ADD SCHEDULE\n";
    cout << "========================================\n";

    cout << "Publisher ID : " << currentID << endl;

    s.scheduleID = defaultScheduleID();

    s.publisherID = currentID;

    s.day = selectDay();

    do
    {
        cout << "\nStarting Time (00:00 - 23:59): ";
        cin >> s.startTime;

        if (!validTime(s.startTime))
        {
            cout << "Invalid time format.\n";
        }

    } while (!validTime(s.startTime));

    do
    {
        cout << "Ending Time (00:00 - 24:00): ";
        cin >> s.endTime;

        if (!validTime(s.endTime))
        {
            cout << "Invalid time format.\n";
        }

    } while (!validTime(s.endTime));

    int start = timeToMinutes(s.startTime);
    int end = timeToMinutes(s.endTime);

    if (end <= start)
    {
        cout << "\nEnding time must be later than starting time.\n";
        return;
    }

    // Check overlapping schedule
    if (scheduleOverlap(s.day, s.startTime, s.endTime))
    {
        cout << "\nThis time overlaps with your existing schedule.\n";
        cout << "Please choose another time.\n";
        return;
    }

    ofstream file("Schedule.txt", ios::app);

    if (!file)
    {
        cout << "\nUnable to open Schedule.txt.\n";
        return;
    }

    file << s.scheduleID << "|"
         << s.publisherID << "|"
         << s.day << "|"
         << s.startTime << "|"
         << s.endTime << endl;

    file.close();

    cout << "\n========================================\n";
    cout << "Schedule added successfully!\n";
    cout << "========================================\n";

    cout << "Schedule ID : " << s.scheduleID << endl;
    cout << "Day         : " << s.day << endl;
    cout << "Time        : " << s.startTime
         << " - " << s.endTime << endl;
}

string defaultScheduleID()
{
    ifstream file("Schedule.txt");

    string line;

    int maxID = 0;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string scheduleID;
        string publisherID;

        getline(ss, scheduleID, '|');
        getline(ss, publisherID, '|');

        // Only check current publisher
        if (publisherID == currentID)
        {
            if (scheduleID.length() > 1)
            {
                string numberPart = scheduleID.substr(1);

                stringstream numberStream(numberPart);

                int number = 0;

                numberStream >> number;

                if (number > maxID)
                    maxID = number;
            }
        }
    }

    file.close();

    maxID++;

    stringstream newID;

    newID << "T";

    if (maxID < 10)
        newID << "0";

    newID << maxID;

    return newID.str();
}

string selectDay()
{
    int choice;

    do
    {
        cout << "\nSelect Day:\n";

        cout << "1. Sunday\n";
        cout << "2. Monday\n";
        cout << "3. Tuesday\n";
        cout << "4. Wednesday\n";
        cout << "5. Thursday\n";
        cout << "6. Friday\n";
        cout << "7. Saturday\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                return "Sunday";

            case 2:
                return "Monday";

            case 3:
                return "Tuesday";

            case 4:
                return "Wednesday";

            case 5:
                return "Thursday";

            case 6:
                return "Friday";

            case 7:
                return "Saturday";

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (true);
}

bool validTime(string time)
{
    if (time.length() != 5)
        return false;

    if (time[2] != ':')
        return false;

    if (time[0] < '0' || time[0] > '2')
        return false;

    if (time[1] < '0' || time[1] > '9')
        return false;

    if (time[3] < '0' || time[3] > '5')
        return false;

    if (time[4] < '0' || time[4] > '9')
        return false;

    int hour =
        (time[0] - '0') * 10 +
        (time[1] - '0');

    int minute =
        (time[3] - '0') * 10 +
        (time[4] - '0');

    if (hour < 0 || hour > 23)
        return false;

    if (minute < 0 || minute > 59)
        return false;

    return true;
}

int timeToMinutes(string time)
{
    int hour =
        (time[0] - '0') * 10 +
        (time[1] - '0');

    int minute =
        (time[3] - '0') * 10 +
        (time[4] - '0');

    return hour * 60 + minute;
}

bool scheduleOverlap(string day, string startTime, string endTime)
{
    ifstream file("Schedule.txt");

    string line;

    int newStart = timeToMinutes(startTime);
    int newEnd = timeToMinutes(endTime);

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

        if (s.publisherID == currentID &&
            s.day == day)
        {
            int oldStart = timeToMinutes(s.startTime);
            int oldEnd = timeToMinutes(s.endTime);

            if (newStart < oldEnd &&
                newEnd > oldStart)
            {
                file.close();
                return true;
            }
        }
    }

    file.close();

    return false;
}
