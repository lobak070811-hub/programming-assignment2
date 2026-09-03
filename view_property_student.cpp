#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

void viewPropertyStudent()//main fucntion
{
    ifstream file("Property.txt");

    if (!file)
    {
        cout << "\nUnable to open Property.txt." << endl;
        return;
    }

    string line;

    int count = 0;
    int displayed = 0;

    cout << "\n========================================" << endl;
    cout << "             PROPERTY LIST" << endl;
    cout << "========================================" << endl;

    while (getline(file, line))
    {
        // Skip empty line
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

        // Read data from Property.txt
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
        p.price = atof(price.c_str());
        p.area = atof(area.c_str());
        p.distance = atof(distance.c_str());
        p.publisherID = atoi(publisherID.c_str());

        count++;
        displayed++;

        cout << "\nProperty " << count << endl;
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

        // Display 5 properties at a time
        if (displayed == 5)
        {
            cout << "\nPress [Enter] to view more...";

            cin.ignore(1000, '\n');
            cin.get();

            displayed = 0;

            cout << "\n========================================" << endl;
            cout << "             PROPERTY LIST" << endl;
            cout << "========================================" << endl;
        }
    }

    // No property found
    if (count == 0)
    {
        cout << "\nNo property available." << endl;
    }
    else
    {
        cout << "\nEnd of property list." << endl;
        cout << "Press [Enter] to return...";

        cin.ignore(1000, '\n');
        cin.get();
    }

    file.close();
}
