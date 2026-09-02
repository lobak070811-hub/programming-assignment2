#include "header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

struct Property
{
    string propertyID;
    string roomType;
    string propertyName;
    string location;
    double price;
    double area;
    double distance;
    string publisherID;
    string publisherName;
    string publisherPhone;
    string publisherRole;
};

void displayProperty(const Property &p);
bool readProperty(string line, Property &p);

void deleteProperty()//main function 
{
    string inputID;
    string line;

    bool found = false;

    cout << "\n=============================\n";
    cout << "       DELETE PROPERTY\n";
    cout << "=============================\n";

    cout << "Enter Property ID: ";
    cin >> inputID;

    ifstream file("Property.txt");//read text file

    if (!file.is_open())
    {
        cout << "\nCannot open Property.txt\n";
        return;
    }

    while (getline(file, line))// Search Property ID
    {
        if (line.empty())
        {
            continue;
        }

        Property p;

        if (readProperty(line, p))
        {
            if (p.propertyID == inputID)
            {
                found = true;
                
                if (p.publisherID != currentID)
				{
    				cout << "\nYou cannot delete this property.\n";
    				cout << "This property belongs to another publisher.\n";

    				file.close();
    				return;
				}

                cout << "\nProperty Found!\n";

                displayProperty(p);

                break;
            }
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nProperty ID not found.\n";
        return;
    }

    // Confirmation
    char choice;

    cout << "\nAre you sure you want to delete this property? (yes(y) or no(n)): ";
    cin >> choice;

    if (choice != 'Y' && choice != 'y')
    {
        cout << "\nDelete cancelled.\n";
        return;
    }

    // Create temporary file
    ifstream inputFile("Property.txt");
    ofstream tempFile("Property_temp.txt");

    if (!inputFile.is_open() || !tempFile.is_open())
    {
        cout << "\nError opening file.\n";
        return;
    }

    // Copy all properties except selected property
    while (getline(inputFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        Property p;

        if (readProperty(line, p))
        {
            if (p.propertyID != inputID)
            {
                tempFile << line << endl;
            }
        }
    }

    inputFile.close();
    tempFile.close();

    // Replace original file
    remove("Property.txt");
    rename("Property_temp.txt", "Property.txt");

    cout << "\nProperty deleted successfully!\n";
}

// Read property information from one line
bool readProperty(string line, Property &p)
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

    stringstream priceConvert(priceString);
    stringstream areaConvert(areaString);
    stringstream distanceConvert(distanceString);

    priceConvert >> p.price;
    areaConvert >> p.area;
    distanceConvert >> p.distance;

    return true;
}

void displayProperty(const Property &p)
{
    cout << "\n====================================\n";
    cout << "          PROPERTY DETAILS\n";
    cout << "====================================\n";

    cout << "Property ID     : " << p.propertyID << endl;
    cout << "Room Type       : " << p.roomType << endl;
    cout << "Property Name   : " << p.propertyName << endl;
    cout << "Location        : " << p.location << endl;
    cout << "Price           : RM" << p.price << endl;
    cout << "Area            : " << p.area << " sqft" << endl;
    cout << "Distance        : " << p.distance << " km" << endl;
    cout << "Published By    : " << p.publisherName << endl;
    cout << "Role            : " << p.publisherRole << endl;
    cout << "Phone           : " << p.publisherPhone << endl;

    cout << "====================================\n";
}
