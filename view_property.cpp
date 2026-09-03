#include "header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

bool readProperty_view(string line, Property &p);
void displayProperty_view(const Property &p);

void viewPropertyPublisher()//main function
{
    ifstream file("Property.txt");

    if (!file.is_open())
    {
        cout << "\nCannot open Property.txt\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\n========================================\n";
    cout << "        MY PUBLISHED PROPERTIES\n";
    cout << "========================================\n";

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        Property p;

        if (readProperty_view(line, p))
        {
            if (p.publisherID == currentID)//check publisher ID = current user ID
            {
                found = true;

                displayProperty_view(p);
                system("pause");
            }
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nYou have not published any property yet.\n";
    }
    
    cout << "\nPress [Enter] to return to the menu...";
    cin.get();
}

// Read one property from Property.txt
bool readProperty_view(string line, Property &p)
{
    stringstream ss(line);

    string priceString;
    string areaString;
    string distanceString;

    getline(ss, p.propertyID, ',');
    getline(ss, p.roomType, ',');
    getline(ss, p.propertyName, ',');
    getline(ss, p.location, ',');

    getline(ss, priceString, ',');
    getline(ss, areaString, ',');
    getline(ss, distanceString, ',');

    getline(ss, p.publisherID, ',');
    getline(ss, p.publisherName, ',');
    getline(ss, p.publisherPhone, ',');
    getline(ss, p.publisherRole);

    // Convert string to double
    stringstream priceConvert(priceString);
    stringstream areaConvert(areaString);
    stringstream distanceConvert(distanceString);

    priceConvert >> p.price;
    areaConvert >> p.area;
    distanceConvert >> p.distance;

    return true;
}

void displayProperty_view(const Property &p)
{
    cout << "\n----------------------------------------\n";

    cout << "Property ID     : " << p.propertyID << endl;
    cout << "Room Type       : " << p.roomType << endl;
    cout << "Property Name   : " << p.propertyName << endl;
    cout << "Location        : " << p.location << endl;
    cout << "Price           : RM" << fixed << setprecision(2) << p.price << endl;
    cout << "Area            : " << p.area << " sqft" << endl;
    cout << "Distance        : " << p.distance << " km" << endl;

    cout << "----------------------------------------\n";
}
