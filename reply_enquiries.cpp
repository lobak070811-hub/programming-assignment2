#include "header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void replyEnquiries()
{
    ifstream file("Enquiry.txt");

    if (!file)
    {
        cout << "\nCannot open Enquiry.txt." << endl;
        return;
    }

    Enquiry enquiries[100];

    int count = 0;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }


        if (count >= 100)
        {
            break;
        }

        stringstream ss(line);

        getline(ss, enquiries[count].enquiryID, '|');
        getline(ss, enquiries[count].studentID, '|');
        getline(ss, enquiries[count].propertyID, '|');
        getline(ss, enquiries[count].publisherID, '|');
        getline(ss, enquiries[count].question, '|');
        getline(ss, enquiries[count].reply);

        count++;
    }

    file.close();

    bool found = false;

    cout << "\n========================================" << endl;
    cout << "             REPLY ENQUIRY" << endl;
    cout << "========================================" << endl;

    cout << "Publisher ID : " << currentID << endl;

    for (int i = 0; i < count; i++)
    {
        if (enquiries[i].publisherID == currentID)
        {
            found = true;

            cout << "\n----------------------------------------" << endl;

            cout << "Enquiry ID  : " << enquiries[i].enquiryID << endl;
            cout << "Student ID  : " << enquiries[i].studentID << endl;
            cout << "Property ID : " << enquiries[i].propertyID << endl;
            cout << "Question    : " << enquiries[i].question << endl;
            cout << "Current Reply: " << enquiries[i].reply << endl;

            cout << "----------------------------------------" << endl;
        }
    }

    if (!found)
    {
        cout << "\nNo enquiries received." << endl;
        return;
    }

    string searchID;

    cout << "\nEnter Enquiry ID to reply: ";
    cin >> searchID;

    bool replyFound = false;

    for (int i = 0; i < count; i++)
    {
        if (enquiries[i].enquiryID == searchID &&
            enquiries[i].publisherID == currentID)
        {
            replyFound = true;

            cin.ignore();

            cout << "\nEnter your reply: ";
            getline(cin, enquiries[i].reply);

            break;
        }
    }

    if (!replyFound)
    {
        cout << "\nEnquiry not found." << endl;
        return;
    }

    ofstream outFile("Enquiry.txt");

    if (!outFile)
    {
        cout << "\nCannot open Enquiry.txt for writing." << endl;
        return;
    }

    for (int i = 0; i < count; i++)
    {
        outFile << enquiries[i].enquiryID << "|"
                << enquiries[i].studentID << "|"
                << enquiries[i].propertyID << "|"
                << enquiries[i].publisherID << "|"
                << enquiries[i].question << "|"
                << enquiries[i].reply
                << endl;
    }

    outFile.close();

    cout << "\n========================================" << endl;
    cout << "          REPLY SENT SUCCESSFULLY" << endl;
    cout << "========================================" << endl;
}
