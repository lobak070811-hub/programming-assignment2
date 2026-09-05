#include "header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void viewEnquiries()
{
    ifstream file("Enquiry.txt");

    if (!file)
    {
        cout << "\nCannot open Enquiry.txt." << endl;
        return;
    }

    string line;
    bool found = false;

    cout << "\n========================================" << endl;
    cout << "          RECEIVED ENQUIRIES" << endl;
    cout << "========================================" << endl;

    cout << "Publisher ID : " << currentID << endl;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        Enquiry e;

        stringstream ss(line);

        getline(ss, e.enquiryID, '|');
        getline(ss, e.studentID, '|');
        getline(ss, e.propertyID, '|');
        getline(ss, e.publisherID, '|');
        getline(ss, e.question, '|');
        getline(ss, e.reply);

        if (e.publisherID == currentID)
        {
            found = true;

            cout << "\n----------------------------------------" << endl;

            cout << "Enquiry ID  : " << e.enquiryID << endl;
            cout << "Student ID  : " << e.studentID << endl;
            cout << "Property ID : " << e.propertyID << endl;
            cout << "Question    : " << e.question << endl;
            cout << "Reply       : " << e.reply << endl;

            cout << "----------------------------------------" << endl;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nNo enquiries received." << endl;
    }
}
