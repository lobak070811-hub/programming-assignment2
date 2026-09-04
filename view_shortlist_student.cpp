#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void viewShortlistStudent()
{
    ifstream shortlistFile("Shortlist.txt");

    if (!shortlistFile)
    {
        cout << "\nNo shortlist available." << endl;
        cout << "Press [Enter] to return...";

        system("pause");
    }

    string line;
    string studentID;
    string propertyID;

    // Store shortlisted Property IDs
    string shortlistedID[100];
    int shortlistCount = 0;

    // Read Shortlist.txt
    while (getline(shortlistFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        getline(ss, studentID, ',');
        getline(ss, propertyID, ',');

        // Check whether the shortlist belongs to current student
        if (studentID == currentID)
        {
            if (shortlistCount < 100)
            {
                shortlistedID[shortlistCount] = propertyID;
                shortlistCount++;
            }
        }
    }

    shortlistFile.close();

    // Student has no shortlisted property
    if (shortlistCount == 0)
    {
        cout << "\n========================================" << endl;
        cout << "             MY SHORTLIST" << endl;
        cout << "========================================" << endl;
        cout << "\nYou have no shortlisted property." << endl;

        system("pause");

        return;
    }

    // Open Property.txt
    ifstream propertyFile("Property.txt");

    if (!propertyFile)
    {
        cout << "\nUnable to open Property.txt." << endl;
        return;
    }

    cout << "\n========================================" << endl;
    cout << "             MY SHORTLIST" << endl;
    cout << "========================================" << endl;

    int displayNumber = 0;

    // Search every shortlisted Property ID
    for (int i = 0; i < shortlistCount; i++)
    {
        // Reset file to beginning
        propertyFile.clear();
        propertyFile.seekg(0);

        bool found = false;

        while (getline(propertyFile, line))
        {
            if (line.empty())
            {
                continue;
            }

            Property p;

            string price;
            string area;
            string distance;
            string publisherID;

            stringstream ss(line);

            getline(ss, p.propertyID, ',');
            getline(ss, p.roomType, ',');
            getline(ss, p.propertyName, ',');
            getline(ss, p.location, ',');
            getline(ss, price, ',');
            getline(ss, area, ',');
            getline(ss, distance, ',');
            getline(ss, publisherID, ',');
            getline(ss, p.publisherName, ',');
            getline(ss, p.publisherPhone, ',');
            getline(ss, p.publisherRole, ',');

            // Convert string to number
            stringstream(price) >> p.price;
            stringstream(area) >> p.area;
            stringstream(distance) >> p.distance;

            // Check Property ID
            if (p.propertyID == shortlistedID[i])
            {
                found = true;
                displayNumber++;

                cout << "\nProperty " << displayNumber << endl;
                cout << "----------------------------------------" << endl;

                cout << "Property ID : " << p.propertyID << endl;
                cout << "Room Type   : " << p.roomType << endl;
                cout << "Property    : " << p.propertyName << endl;
                cout << "Location    : " << p.location << endl;
                cout << "Price       : RM " << p.price << endl;
                cout << "Area        : " << p.area << " sqft" << endl;
                cout << "Distance    : " << p.distance << " km" << endl;

                cout << "Publisher   : " << p.publisherName << endl;
                cout << "Phone       : " << p.publisherPhone << endl;
                cout << "Role        : " << p.publisherRole << endl;

                cout << "----------------------------------------" << endl;

                break;
            }
        }

        // Property was deleted but still exists in Shortlist.txt
        if (!found)
        {
            cout << "\nProperty ID " << shortlistedID[i]
                 << " is no longer available." << endl;
        }
    }

    propertyFile.close();

    system("pause"); 
}
