#include "header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string defaultEnquiryID();

void sendEnquiry();
void inputEnquiry();
void displaySentEnquiry(const Enquiry &e);

void sendEnquiry()//main function
{
    cout << "\n========================================" << endl;
    cout << "              SEND ENQUIRY" << endl;
    cout << "========================================" << endl;

    cout << "Student ID : " << currentID << endl;

    inputEnquiry();
}

string defaultEnquiryID()
{
    ifstream file("Enquiry.txt");

    int maxID = 0;
    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string enquiryID;
        getline(ss, enquiryID, '|');

        if (enquiryID.length() > 1)
        {
            string numberPart = enquiryID.substr(1);

            int number = 0;

            stringstream convert(numberPart);
            convert >> number;

            if (number > maxID)
            {
                maxID = number;
            }
        }
    }

    file.close();

    maxID++;

    string numberString;
    stringstream convertID;

    convertID << maxID;
    numberString = convertID.str();

    string newID;

    if (maxID < 10)
    {
        newID = "E00" + numberString;
    }
    else if (maxID < 100)
    {
        newID = "E0" + numberString;
    }
    else
    {
        newID = "E" + numberString;
    }

    return newID;
}

void inputEnquiry()
{
    Enquiry e;
    
    e.enquiryID = defaultEnquiryID();

    e.studentID = currentID;

    cout << "\nEnter Property ID: ";
    cin >> e.propertyID;

    ifstream propertyFile("Property.txt");

    if (!propertyFile)
    {
        cout << "\nCannot open Property.txt." << endl;
        return;
    }


    string line;
    bool propertyFound = false;

    while (getline(propertyFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string propertyID;
        string roomType;
        string propertyName;
        string location;
        string price;
        string area;
        string distance;
        string publisherID;
        string publisherName;
        string publisherPhone;
        string publisherRole;

        getline(ss, propertyID, ',');
        getline(ss, roomType, ',');
        getline(ss, propertyName, ',');
        getline(ss, location, ',');
        getline(ss, price, ',');
        getline(ss, area, ',');
        getline(ss, distance, ',');
        getline(ss, publisherID, ',');
        getline(ss, publisherName, ',');
        getline(ss, publisherPhone, ',');
        getline(ss, publisherRole);

        // Check Property ID
        if (propertyID == e.propertyID)
        {
            propertyFound = true;

            // Automatically get Publisher ID
            e.publisherID = publisherID;


            cout << "\n========================================" << endl;
            cout << "           PROPERTY FOUND" << endl;
            cout << "========================================" << endl;

            cout << "Property ID   : " << propertyID << endl;
            cout << "Property Name : " << propertyName << endl;
            cout << "Room Type     : " << roomType << endl;
            cout << "Location      : " << location << endl;
            cout << "Price         : RM" << price << endl;

            cout << "\nPublisher ID   : " << publisherID << endl;
            cout << "Publisher Name : " << publisherName << endl;
            cout << "Publisher Role : " << publisherRole << endl;

            cout << "========================================" << endl;

            break;
        }
    }

    propertyFile.close();

    if (!propertyFound)
    {
        cout << "\nProperty ID not found." << endl;
        cout << "Please enter a valid Property ID." << endl;

        return;
    }

    cin.ignore();

    cout << "\nEnter your enquiry: ";
    getline(cin, e.question);

    e.reply = "No reply yet.";//default reply

    ofstream file("Enquiry.txt", ios::app);

    if (!file)
    {
        cout << "\nCannot open Enquiry.txt." << endl;
        return;
    }

    file << e.enquiryID << "|"
         << e.studentID << "|"
         << e.propertyID << "|"
         << e.publisherID << "|"
         << e.question << "|"
         << e.reply
         << endl;

    file.close();

    displaySentEnquiry(e);
}

void displaySentEnquiry(const Enquiry &e)
{
    cout << "\n========================================" << endl;
    cout << "       ENQUIRY SENT SUCCESSFULLY" << endl;
    cout << "========================================" << endl;

    cout << "Enquiry ID  : " << e.enquiryID << endl;
    cout << "Student ID  : " << e.studentID << endl;
    cout << "Property ID : " << e.propertyID << endl;
    cout << "Publisher ID: " << e.publisherID << endl;
    cout << "Question    : " << e.question << endl;
    cout << "Status      : No reply yet." << endl;

    cout << "========================================" << endl;
}
