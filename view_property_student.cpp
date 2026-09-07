#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cctype>

using namespace std;

bool readPropertyStudent(string line, Property &p);

void viewPropertyStudent()
{
    ifstream file("Property.txt");

    if (!file)
    {
        cout << "\nUnable to open Property.txt." << endl;
        return;
    }

    string line;

    int count = 0;

    char choice;

    while (getline(file, line))
    {
        // Skip empty line
        if (line.empty())
        {
            continue;
        }

        Property p;

        // Read property information
        if (!readPropertyStudent(line, p))
        {
            continue;
        }

        count++;

        cout << "\n========================================\n";
        cout << "              PROPERTY " << count << endl;
        cout << "========================================\n";

        cout << "Property ID : " << p.propertyID << endl;
        cout << "Room Type   : " << p.roomType << endl;
        cout << "Property    : " << p.propertyName << endl;
        cout << "Location    : " << p.location << endl;
        cout << "Price       : RM " << fixed << setprecision(2) << p.price << endl;
        cout << "Area        : " << fixed << setprecision(2) << p.area << " sqft" << endl;
        cout << "Distance    : " << fixed << setprecision(2) << p.distance << " km" << endl;
        cout << "Publisher   : " << p.publisherName << endl; 
        cout << "Phone       : " << p.publisherPhone << endl;
        cout << "Role        : " << p.publisherRole << endl;

        cout << "----------------------------------------" << endl;

        displayPropertyReview(p.propertyID);

        cout << "\nView next property? (Yes(y)/No(n)): ";
        cin >> choice;

        choice = toupper(choice);

        while (choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n')
        {
            cout << "\nInvalid input.";
            cout << "\nPlease enter Y or N: ";

            cin >> choice;

            choice = toupper(choice);
        }

        if (choice == 'N' || choice == 'n')
        {
            cout << "\nReturning to Student Menu...\n";
            break;
        }
    }

    if (count == 0)
    {
        cout << "\nNo property available." << endl;
    }

    file.close();
}

bool readPropertyStudent(string line, Property &p)
{
    stringstream ss(line);

    string price;
    string area;
    string distance;

    getline(ss, p.propertyID, ',');
    getline(ss, p.roomType, ',');
    getline(ss, p.propertyName, ',');
    getline(ss, p.location, ',');

    getline(ss, price, ',');
    getline(ss, area, ',');
    getline(ss, distance, ',');

    getline(ss, p.publisherID, ',');
    getline(ss, p.publisherName, ',');
    getline(ss, p.publisherPhone, ',');
    getline(ss, p.publisherRole);

    p.price = atof(price.c_str());
    p.area = atof(area.c_str());
    p.distance = atof(distance.c_str());

    return true;
}
