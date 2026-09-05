#include "header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void viewEnquiriesReply()
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
    cout << "             MY ENQUIRIES" << endl;
    cout << "========================================" << endl;

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

        if (e.studentID == currentID)
        {
            found = true;

            cout << "\n----------------------------------------" << endl;

            cout << "Enquiry ID   : " << e.enquiryID << endl;
            cout << "Property ID  : " << e.propertyID << endl;
            cout << "Publisher ID : " << e.publisherID << endl;
            cout << "Question     : " << e.question << endl;
            cout << "Reply        : " << e.reply << endl;

            cout << "----------------------------------------" << endl;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nYou have not sent any enquiries yet." << endl;
    }
}
