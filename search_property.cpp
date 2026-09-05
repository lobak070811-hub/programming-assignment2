#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

bool selectedRoom[3];
bool usePrice;
bool useDistance;

void selectRoomType(bool selectedRoom[]); 
int selectPropertyName(string selectedNames[]);
void inputPriceRange(bool &usePrice, double &minPrice, double &maxPrice);
void inputDistanceRange(bool &useDistance, double &minDistance, double &maxDistance);
void displaySearchResult(bool selectedRoom[], string selectedNames[], int selectedNameCount, bool usePrice, double minPrice,
                         double maxPrice, bool useDistance, double minDistance, double maxDistance);

void searchProperty()//main function
{
    bool selectedRoom[3];

    string selectedNames[100];//which property name does student choose
    int selectedNameCount;//how much property name does student choose

    bool usePrice;
    bool useDistance;

    double minPrice = 0;
    double maxPrice = 0;

    double minDistance = 0;
    double maxDistance = 0;

    selectRoomType(selectedRoom);

    selectedNameCount = selectPropertyName(selectedNames);

    if (selectedNameCount == 0)
    {
        cout << "\nNo property name selected." << endl;
        cout << "Search cancelled." << endl;

        system("pause");

        return;
    }

    inputPriceRange(usePrice, minPrice, maxPrice);

    inputDistanceRange(useDistance, minDistance, maxDistance);

    displaySearchResult(selectedRoom, selectedNames, selectedNameCount, usePrice, minPrice, maxPrice, useDistance, minDistance, maxDistance);
}

void selectRoomType(bool selectedRoom[])
{
    int choice;
    char again;
	
	//initialize the choice as false
    selectedRoom[0] = false;
    selectedRoom[1] = false;
    selectedRoom[2] = false;

    do
    {
        cout << "\n========================================" << endl;
        cout << "             SELECT ROOM TYPE" << endl;
        cout << "========================================" << endl;
        cout << "1. Master Room" << endl;
        cout << "2. Middle Room" << endl;
        cout << "3. Small Room" << endl;
        cout << "========================================" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3)
        {
            selectedRoom[choice - 1] = true;

            cout << "\nRoom type selected successfully." << endl;
        }
        else
        {
            cout << "\nInvalid choice. Please try again." << endl;
            continue;
        }

        cout << "Do you want to select another room type? (Yes(y)/No(n)): ";
        cin >> again;

    } while (again == 'Y' || again == 'y');

}

int getPropertyNames(string propertyNames[])
{
    ifstream file("Property.txt");

    if (!file)
    {
        cout << "\nUnable to open Property.txt." << endl;
        return 0;
    }

    string line;
    int nameCount = 0;//initialize the number of property name

    while (getline(file, line))
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

        //Check whether property name already exists, initialize it doesn't exist at first
        bool duplicate = false;

        for (int i = 0; i < nameCount; i++)
        {
            if (propertyNames[i] == p.propertyName)
            {
                duplicate = true;//The property name is already exist
                break;
            }
        }

        if (!duplicate && nameCount < 100)//if no exist
        {
            propertyNames[nameCount] = p.propertyName;//save into array
            nameCount++;
        }
    }

    file.close();

    return nameCount;//the numbers of property name do text file have
}

int selectPropertyName(string selectedNames[])
{
    string propertyNames[100];

    int nameCount = getPropertyNames(propertyNames);

    if (nameCount == 0)
    {
        cout << "\nNo property name available." << endl;
        return 0;
    }

    cout << "\n========================================" << endl;
    cout << "           SELECT PROPERTY NAME" << endl;
    cout << "========================================" << endl;

    for (int i = 0; i < nameCount; i++)
    {
        cout << i + 1 << ". " << propertyNames[i] << endl;
    }

    cout << "========================================" << endl;
    cout << "Enter 0 when you finish selecting." << endl;

    int choice;
    int selectedCount = 0;

    while (true)
    {
        cout << "\nEnter property name number: ";
        cin >> choice;

        if (choice == 0)
        {
            break;
        }

        if (choice < 1 || choice > nameCount)
        {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        // Check duplicate selection
        bool alreadySelected = false;

        for (int i = 0; i < selectedCount; i++)
        {
            if (selectedNames[i] == propertyNames[choice - 1])
            {
                alreadySelected = true;
                break;
            }
        }

        if (alreadySelected)
        {
            cout << "This property name has already been selected." << endl;
        }
        else
        {
            selectedNames[selectedCount] = propertyNames[choice - 1];
            selectedCount++;

            cout << "Selected: "
                 << propertyNames[choice - 1] << endl;
        }
    }

    return selectedCount;
}

void inputPriceRange(bool &usePrice, double &minPrice, double &maxPrice)
{
    char choice;

    cout << "\n========================================" << endl;
    cout << "              PRICE RANGE" << endl;
    cout << "========================================" << endl;

    cout << "Do you want to set a price range? (Yes(y)/No(n)): ";
    cin >> choice;

    if (choice == 'N' || choice == 'n')
    {
        usePrice = false;
        return;
    }

    usePrice = true;//using pass-by-reference, return value but not 'true'

    while (true)
    {
        cout << "Enter minimum price: RM ";
        cin >> minPrice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        cout << "Enter maximum price: RM ";
        cin >> maxPrice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (minPrice < 0 || maxPrice < 0)
        {
            cout << "Price cannot be negative." << endl;
        }
        else if (minPrice > maxPrice)
        {
            cout << "Minimum price cannot be greater than maximum price." << endl;
        }
        else
        {
            break;
        }
    }
}

void inputDistanceRange(bool &useDistance, double &minDistance, double &maxDistance)
{
    char choice;

    cout << "\n========================================" << endl;
    cout << "            DISTANCE RANGE" << endl;
    cout << "========================================" << endl;

    cout << "Do you want to set a distance range? (Yes(y)/No(n)): ";
    cin >> choice;

    if (choice == 'N' || choice == 'n')
    {
        useDistance = false;
        return;
    }

    useDistance = true;

    while (true)
    {
        cout << "Enter minimum distance (km): ";
        cin >> minDistance;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        cout << "Enter maximum distance (km): ";
        cin >> maxDistance;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (minDistance < 0 || maxDistance < 0)
        {
            cout << "Distance cannot be negative." << endl;
        }
        else if (minDistance > maxDistance)
        {
            cout << "Minimum distance cannot be greater than maximum distance." << endl;
        }
        else
        {
            break;
        }
    }
}

bool checkRoomType(string propertyRoomType, bool selectedRoom[])
{
    // Convert property room type to lowercase
    for (int i = 0; i < propertyRoomType.length(); i++)
    {
        propertyRoomType[i] = tolower(propertyRoomType[i]);
    }

    if (selectedRoom[0] && propertyRoomType.find("master") != string::npos)
    {
        return true;
    }

    if (selectedRoom[1] && propertyRoomType.find("middle") != string::npos)
    {
        return true;
    }

    if (selectedRoom[2] && propertyRoomType.find("small") != string::npos)
    {
        return true;
    }

    return false;
}

bool checkPropertyName(string propertyName, string selectedNames[], int selectedNameCount)
{
    for (int i = 0; i < selectedNameCount; i++)
    {
        if (propertyName == selectedNames[i])
        {
            return true;
        }
    }

    return false;
}

void displaySearchResult(bool selectedRoom[], string selectedNames[], int selectedNameCount, bool usePrice, double minPrice,
                         double maxPrice, bool useDistance, double minDistance, double maxDistance)
{
    ifstream file("Property.txt");

    if (!file)
    {
        cout << "\nUnable to open Property.txt." << endl;
        return;
    }

    string line;
    int resultCount = 0;

    cout << "\n========================================" << endl;
    cout << "          SEARCH RESULT" << endl;
    cout << "========================================" << endl;

    while (getline(file, line))
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

        stringstream(price) >> p.price;
        stringstream(area) >> p.area;
        stringstream(distance) >> p.distance;
        p.publisherID = publisherID; 

        // Check room type
        if (!checkRoomType(p.roomType, selectedRoom))
        {
            continue;
        }

        // Check property name
        if (!checkPropertyName(p.propertyName, selectedNames, selectedNameCount))
        {
            continue;
        }

        // Check price
        if (usePrice)
        {
            if (p.price < minPrice || p.price > maxPrice)
            {
                continue;
            }
        }

        // Check distance
        if (useDistance)
        {
            if (p.distance < minDistance || p.distance > maxDistance)
            {
                continue;
            }
        }

        // All conditions satisfied
        resultCount++;

        cout << "\nProperty " << resultCount << endl;
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
    }

    file.close();

    if (resultCount == 0)
    {
        cout << "\nNo property matches your search criteria." << endl;
    }
    else
    {
        cout << "\nTotal properties found: "
             << resultCount << endl;
    }

    system("pause");
}
