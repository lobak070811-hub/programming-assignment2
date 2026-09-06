#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void checkAppointmentStatus()
{
    ifstream file("Appointment.txt");

    if (!file)
    {
        cout << "\nYou have no appointment.\n";
        return;
    }

    string line;

    bool found = false;

    cout << "\n========================================\n";
    cout << "        MY APPOINTMENT STATUS\n";
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

        // Only show current student's appointments
        if (a.studentID == currentID)
        {
            found = true;

            cout << "\nAppointment ID : " << a.appointmentID;
            cout << "\nPublisher ID   : " << a.publisherID;
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
                cout << "\nReason         : "
                     << a.reason;
            }

            if (a.status == "Pending")
            {
                cout << "\nMessage        : Waiting for publisher confirmation.";
            }

            if (a.status == "Accepted")
            {
                cout << "\nMessage        : Your house viewing has been accepted.";
            }

            cout << "\n----------------------------------------\n";
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nYou have no appointment.\n";
    }
}
