#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool validDate(string date);
bool displayPublisherSchedule(string publisherID);
bool appointmentExists(string publisherID, string scheduleID, string date);

string defaultAppointmentID();
string getDayOfWeek(string date);

void makeAppointment()//main function
{
    string publisherID;

    cout << "\n========================================\n";
    cout << "           MAKE APPOINTMENT\n";
    cout << "========================================\n";

    cout << "Student ID : " << currentID << endl;

    cout << "\nEnter Publisher ID: ";
    cin >> publisherID;

    // Display publisher schedule
    if (!displayPublisherSchedule(publisherID))
    {
        cout << "\nThis publisher has no available schedule.\n";
        return;
    }

    string date;

    cout << "\nEnter viewing date (YYYY-MM-DD): ";
    cin >> date;

    while (!validDate(date))
    {
        cout << "Invalid date format.\n";
        cout << "Please enter YYYY-MM-DD: ";
        cin >> date;
    }

    string selectedDay = getDayOfWeek(date);

    cout << "\nSelected Date : " << date;
    cout << "\nDay           : " << selectedDay << endl;

    string scheduleID;

    cout << "\nEnter Schedule ID: ";
    cin >> scheduleID;
 
    // Find selected schedule
    ifstream scheduleFile("Schedule.txt");

    if (!scheduleFile)
    {
        cout << "\nUnable to open Schedule.txt.\n";
        return;
    }

    string line;

    Schedule selectedSchedule;

    bool found = false;

    while (getline(scheduleFile, line))
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

        if (s.scheduleID == scheduleID &&
            s.publisherID == publisherID)
        {
            selectedSchedule = s;
            found = true;
            break;
        }
    }

    scheduleFile.close();

    if (!found)
    {
        cout << "\nInvalid Schedule ID for this Publisher.\n";
        return;
    }

    // Check whether selected date matches schedule day
    if (selectedSchedule.day != selectedDay)
    {
        cout << "\nThis Schedule is only available on "
             << selectedSchedule.day << ".\n";

        cout << "Please select another date.\n";
        return;
    }

    // Check whether already booked
    if (appointmentExists(publisherID, scheduleID, date))
    {
        cout << "\n========================================\n";
        cout << "This time has already been booked.\n";
        cout << "Please choose another date or schedule.\n";
        cout << "========================================\n";

        return;
    }

    // Ask Property ID
    string propertyID;

    cout << "\nEnter Property ID for viewing: ";
    cin >> propertyID;

    // Create appointment
    Appointment a;

    a.appointmentID = defaultAppointmentID();

    a.studentID = currentID;

    a.publisherID = publisherID;

    a.propertyID = propertyID;

    a.scheduleID = scheduleID;

    a.date = date;

    a.day = selectedSchedule.day;

    a.startTime = selectedSchedule.startTime;

    a.endTime = selectedSchedule.endTime;

    a.status = "Pending";

    a.reason = "-";

    ofstream file("Appointment.txt", ios::app);

    if (!file)
    {
        cout << "\nUnable to open Appointment.txt.\n";
        return;
    }

    file << a.appointmentID << "|"
         << a.studentID << "|"
         << a.publisherID << "|"
         << a.propertyID << "|"
         << a.scheduleID << "|"
         << a.date << "|"
         << a.day << "|"
         << a.startTime << "|"
         << a.endTime << "|"
         << a.status << "|"
         << a.reason
         << endl;

    file.close();

    cout << "\n========================================\n";
    cout << "Appointment submitted successfully!\n";
    cout << "========================================\n";

    cout << "Appointment ID : " << a.appointmentID << endl;
    cout << "Publisher ID   : " << a.publisherID << endl;
    cout << "Property ID    : " << a.propertyID << endl;
    cout << "Date           : " << a.date << endl;
    cout << "Day            : " << a.day << endl;
    cout << "Time           : "
         << a.startTime << " - "
         << a.endTime << endl;
    cout << "Status         : Pending\n";
}

string defaultAppointmentID()
{
    ifstream file("Appointment.txt");

    string line;

    int maxID = 0;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string id;

        getline(ss, id, '|');

        if (id.length() > 2)
        {
            string numberPart = id.substr(2);

            stringstream ns(numberPart);

            int number = 0;

            ns >> number;

            if (number > maxID)
                maxID = number;
        }
    }

    file.close();

    maxID++;

    stringstream newID;

    newID << "AP";

    if (maxID < 10)
        newID << "00";
    else if (maxID < 100)
        newID << "0";

    newID << maxID;

    return newID.str();
}

bool validDate(string date)
{
    if (date.length() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    return true;
}

string getDayOfWeek(string date)
{
    int year =
        (date[0] - '0') * 1000 +
        (date[1] - '0') * 100 +
        (date[2] - '0') * 10 +
        (date[3] - '0');

    int month =
        (date[5] - '0') * 10 +
        (date[6] - '0');

    int day =
        (date[8] - '0') * 10 +
        (date[9] - '0');

    if (month < 3)
    {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;

    int h =
        (day +
         (13 * (month + 1)) / 5 +
         k +
         k / 4 +
         j / 4 +
         5 * j) % 7;

    string days[7] =
    {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday"
    };

    return days[h];
}

bool displayPublisherSchedule(string publisherID)
{
    ifstream file("Schedule.txt");

    if (!file)
    {
        cout << "\nNo schedule available.\n";
        return false;
    }

    string line;

    bool found = false;

    cout << "\n========================================\n";
    cout << "       PUBLISHER AVAILABLE SCHEDULE\n";
    cout << "========================================\n";

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

        if (s.publisherID == publisherID)
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

    return found;
}

bool appointmentExists(string publisherID, string scheduleID, string date)
{
    ifstream file("Appointment.txt");

    if (!file)
        return false;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        Appointment a;

        getline(ss, a.appointmentID, '|');
        getline(ss, a.studentID, '|');
        getline(ss, a.publisherID, '|');
        getline(ss, a.propertyID, '|');
        getline(ss, a.scheduleID, '|');
        getline(ss, a.date, '|');
        getline(ss, a.day, '|');
        getline(ss, a.startTime, '|');
        getline(ss, a.endTime, '|');
        getline(ss, a.status, '|');
        getline(ss, a.reason);

        if (a.publisherID == publisherID &&
            a.scheduleID == scheduleID &&
            a.date == date &&
            a.status != "Rejected")
        {
            file.close();
            return true;
        }
    }

    file.close();

    return false;
}
