#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

void addShortlist()
{
    string searchID;
    string line;
    bool found = false;

    cout << "\n========================================" << endl;
    cout << "             ADD SHORTLIST" << endl;
    cout << "========================================" << endl;

    cout << "Enter Property ID: ";
    cin >> searchID;

    ifstream propertyFile("Property.txt");

    if (!propertyFile)
    {
        cout << "\nUnable to open Property.txt." << endl;
        return;
    }

    Property p;

    // Search Property.txt
    while (getline(propertyFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string price;
        string area;
        string distance;
        string publisherID;

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

        p.price = atof(price.c_str());
        p.area = atof(area.c_str());
        p.distance = atof(distance.c_str());
        p.publisherID = atoi(publisherID.c_str());

        if (p.propertyID == searchID)
        {
            found = true;
            break;
        }
    }

    propertyFile.close();

    // Property not found
    if (!found)
    {
        cout << "\nProperty ID not found." << endl;
        system("pause");

        return;
    }

    // Display Property
    cout << "\n========================================" << endl;
    cout << "             PROPERTY FOUND" << endl;
    cout << "========================================" << endl;

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

    cout << "========================================" << endl;

    // Check whether already shortlisted
    ifstream shortlistFile("Shortlist.txt");

    bool alreadyShortlisted = false;

    if (shortlistFile)
    {
        string shortlistLine;

        while (getline(shortlistFile, shortlistLine))
        {
            if (shortlistLine.empty())
            {
                continue;
            }

            string studentID;
            string propertyID;

            stringstream ss(shortlistLine);

            getline(ss, studentID, ',');
            getline(ss, propertyID, ',');

            if (studentID == currentID && propertyID == searchID)
            {
                alreadyShortlisted = true;
                break;
            }
        }

        shortlistFile.close();
    }

    if (alreadyShortlisted)
    {
        cout << "\nYou have already shortlisted this property." << endl;
        system("pause");

        return;
    }

    // Ask for confirmation
    char confirmation;

    cout << "\nDo you want to add this property to your shortlist?" << endl;
    cout << "Enter Y to confirm or N to cancel: ";
    cin >> confirmation;

    if (confirmation == 'Y' || confirmation == 'y')
    {
        ofstream file("Shortlist.txt", ios::app);

        if (!file)
        {
            cout << "\nUnable to open Shortlist.txt." << endl;
            return;
        }

        // Student ID, Property ID
        file << currentID << "," << p.propertyID << endl;

        file.close();

        cout << "\nProperty successfully added to your shortlist!" << endl;
    }
    else
    {
        cout << "\nProperty was not added to shortlist." << endl;
    }

	system("pause");
}
