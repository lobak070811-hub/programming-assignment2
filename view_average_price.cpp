#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

bool readProperty_average(string line, Property &p);
double calculatePricePerSqft(const Property &p);
double findMaxDistance();
void displayAveragePrice(double lowerBound, double upperBound);

void viewAveragePrice() // main function
{
    double lowerBound;
    double upperBound;
    double maxDistance;

    char continueChoice;

    cout << "\n========================================\n";
    cout << "           VIEW AVERAGE PRICE\n";
    cout << "========================================\n";

    cout << "Publisher ID : " << currentID << endl;

    // Find the furthest distance in Property.txt
    maxDistance = findMaxDistance();

    if (maxDistance <= 0)
    {
        cout << "\nNo property data available.\n";
        system("pause");
        return;
    }

    do
    {
        cout << "\n========================================\n";
        cout << "        SEARCH DISTANCE RANGE\n";
        cout << "========================================\n";

        cout << "Furthest distance : "
             << fixed
             << setprecision(2)
             << maxDistance
             << " km\n";

        while (true)
        {
            cout << "\nEnter lower distance: ";
            cin >> lowerBound;

            // Check lower distance
            if (lowerBound < 0)
            {
                cout << "\nInvalid input.";
                cout << "\nDistance cannot be less than 0.\n";

                // Go back and ask for lower distance again
                continue;
            }

            // Lower distance is valid
            break;
        }

        while (true)
        {
            cout << "Enter upper distance: ";
            cin >> upperBound;

            if (upperBound < 0)
            {
                cout << "\nInvalid input.";
                cout << "\nDistance cannot be less than 0.\n";

                // Ask for upper distance again
                continue;
            }

            if (upperBound < lowerBound)
            {
                cout << "\nInvalid input.";
                cout << "\nUpper distance cannot be less than "
                     << "lower distance.\n";

                // Ask for upper distance again
                continue;
            }

            if (upperBound > maxDistance)
            {
                cout << "\nInvalid input.";

                cout << "\nThe furthest distance is "
                     << fixed
                     << setprecision(2)
                     << maxDistance
                     << " km.\n";

                cout << "Please enter the upper distance again.\n";

                // Ask for upper distance again
                continue;
            }

            // Upper distance is valid
            break;
        }

        displayAveragePrice(lowerBound, upperBound);

        cout << "\nDo you want to search another distance range? (Y/N): ";
        cin >> continueChoice;

        continueChoice = toupper(continueChoice);

    } while (continueChoice == 'Y');

    cout << "\nReturning to previous menu...\n";
}

bool readProperty_average(string line, Property &p)
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

double calculatePricePerSqft(const Property &p)
{
    if (p.area <= 0)
    {
        return 0;
    }

    return p.price / p.area;
}

double findMaxDistance()
{
    ifstream file("Property.txt");


    if (!file.is_open())
    {
        return 0;
    }

    string line;

    double maxDistance = 0;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        Property p;

        if (readProperty_average(line, p))
        {
            if (p.distance > maxDistance)
            {
                maxDistance = p.distance;
            }
        }
    }

    file.close();

    return maxDistance;
}

void displayAveragePrice(double lowerBound, double upperBound)
{
    ifstream file("Property.txt");

    if (!file.is_open())
    {
        cout << "\nCannot open Property.txt\n";
        return;
    }

    string line;
    
	//current publisher
    bool hasOwnProperty = false;

    double ownTotal = 0;
    int ownCount = 0;

    string ownPropertyDetails = "";
	
	//neighbour property
    double neighbourTotal = 0;
    int neighbourCount = 0;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        Property p;

        if (!readProperty_average(line, p))
        {
            continue;
        }

        if (p.distance < lowerBound || p.distance > upperBound)//if satisfied 
        {
            continue;
        }

        // Calculate RM/sqft
        double pricePerSqft = calculatePricePerSqft(p);

        if (pricePerSqft <= 0)
        {
            continue;
        }

        if (p.publisherID == currentID)//current user property
        {
            hasOwnProperty = true;

            ownTotal += pricePerSqft;
            ownCount++;

            // Store property details
            stringstream detail;

            detail << "Property ID : "
                   << p.propertyID
                   << "\n";

            detail << "Area        : "
                   << fixed
                   << setprecision(2)
                   << p.area
                   << " sqft\n";

            detail << "Price       : RM "
                   << fixed
                   << setprecision(2)
                   << p.price
                   << "\n";

            detail << "Price/sqft  : RM "
                   << fixed
                   << setprecision(2)
                   << pricePerSqft
                   << "/sqft\n";

            detail << "----------------------------------------\n";

            ownPropertyDetails += detail.str();
        }

        else
        {
            neighbourTotal += pricePerSqft;
            neighbourCount++;
        }
    }

    file.close();
	
	//display selected range
    cout << "\n========================================\n";

    cout << "Distance range : "
         << fixed
         << setprecision(2)
         << lowerBound
         << " - "
         << upperBound
         << " km\n";

    cout << "========================================\n";
	
	//diaplay own property
    if (hasOwnProperty)
    {
        cout << "\nYour properties:\n";

        cout << "----------------------------------------\n";

        cout << ownPropertyDetails;

        // Calculate own average
        double ownAverage =
            ownTotal / ownCount;

        cout << "\nYour properties average price : RM "
             << fixed
             << setprecision(2)
             << ownAverage
             << "/sqft\n";
    }
    else
    {
        cout << "\nYou do not have any property "
             << "in this distance range.\n";
    }
	
	//display other neighbour average price
    if (neighbourCount > 0)
    {
        double neighbourAverage = neighbourTotal / neighbourCount;

        cout << "\nOther properties average price : RM "
             << fixed
             << setprecision(2)
             << neighbourAverage
             << "/sqft\n";
    }
    else
    {
        cout << "\nOther properties average price : N/A\n";
    }

    cout << "\n========================================\n";
}
