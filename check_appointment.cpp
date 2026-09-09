#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void checkAppointment()
{
    ifstream file("Appointment.txt");

    if (!file)
    {
        cout << "\nNo appointment received yet.\n";
        
        system("pause");
        return;
    }

    string line;

    bool found = false;

    cout << "\n========================================\n";
    cout << "        RECEIVED APPOINTMENTS\n";
    cout << "========================================\n";

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

        if (a.publisherID == currentID)
        {
            found = true;

            cout << "\nAppointment ID : " << a.appointmentID;
            cout << "\nStudent ID     : " << a.studentID;
            cout << "\nProperty ID    : " << a.propertyID;
            cout << "\nSchedule ID    : " << a.scheduleID;
            cout << "\nDate           : " << a.date;
            cout << "\nDay            : " << a.day;
            cout << "\nTime           : "
                 << a.startTime << " - "
                 << a.endTime;
            cout << "\nStatus         : " << a.status;

            if (a.status == "Rejected")
            {
                cout << "\nReason         : " << a.reason;
            }

            cout << "\n----------------------------------------\n";
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nNo appointment received.\n";
        
        system("pause");
        return;
    }

    // Select appointment
    string appointmentID;

    cout << "\nEnter Appointment ID to process: ";
    cin >> appointmentID;

    // Read all records
    ifstream input("Appointment.txt");

    Appointment appointments[100];

    int count = 0;

    while (getline(input, line) && count < 100)
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        getline(ss, appointments[count].appointmentID, '|');
        getline(ss, appointments[count].studentID, '|');
        getline(ss, appointments[count].publisherID, '|');
        getline(ss, appointments[count].propertyID, '|');
        getline(ss, appointments[count].scheduleID, '|');
        getline(ss, appointments[count].date, '|');
        getline(ss, appointments[count].day, '|');
        getline(ss, appointments[count].startTime, '|');
        getline(ss, appointments[count].endTime, '|');
        getline(ss, appointments[count].status, '|');
        getline(ss, appointments[count].reason);

        count++;
    }

    input.close();

    int selected = -1;

    for (int i = 0; i < count; i++)
    {
        if (appointments[i].appointmentID == appointmentID &&
            appointments[i].publisherID == currentID)
        {
            selected = i;
            break;
        }
    }

    if (selected == -1)
    {
        cout << "\nAppointment not found.\n";
        
        system("pause");
        return;
    }

    if (appointments[selected].status != "Pending")
    {
        cout << "\nThis appointment has already been processed.\n";
        
        system("pause");
        return;
    }

    int choice;

    cout << "\n========================================\n";
    cout << "1. Accept Appointment";
    cout << "\n2. Reject Appointment";
    cout << "\n========================================\n";

    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
        appointments[selected].status = "Accepted";

        appointments[selected].reason = "-";
    }
    else if (choice == 2)
    {
        appointments[selected].status = "Rejected";

        cin.ignore();

        cout << "\nEnter rejection reason: ";
        getline(cin, appointments[selected].reason);
    }
    else
    {
        cout << "\nInvalid choice.\n";
        return;
    }

    // Rewrite Appointment.txt
    ofstream output("Appointment.txt");

    if (!output)
    {
        cout << "\nUnable to update Appointment.txt.\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        output << appointments[i].appointmentID << "|"
               << appointments[i].studentID << "|"
               << appointments[i].publisherID << "|"
               << appointments[i].propertyID << "|"
               << appointments[i].scheduleID << "|"
               << appointments[i].date << "|"
               << appointments[i].day << "|"
               << appointments[i].startTime << "|"
               << appointments[i].endTime << "|"
               << appointments[i].status << "|"
               << appointments[i].reason
               << endl;
    }

    output.close();
 
    cout << "\nAppointment updated successfully.\n";
    
    system("pause");
}
