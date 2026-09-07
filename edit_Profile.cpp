#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void editProfile()
{
    string newName;
    string newPhone;
    string newEmail;

    cout << "\n========================================\n";
    cout << "             EDIT PROFILE\n";
    cout << "========================================\n";

    cout << "ID : " << currentID << endl;

    cout << "\nEnter new name: ";
    cin.ignore();
    getline(cin, newName);

    cout << "Enter new phone number: ";
    getline(cin, newPhone);

    cout << "Enter new email: ";
    getline(cin, newEmail);

    string fileName;

    // Determine which file to update
    if (currentRole == "Student")
    {
        fileName = "Student.txt";
    }
    else if (currentRole == "Owner")
    {
        fileName = "Owner.txt";
    }
    else if (currentRole == "Agent")
    {
        fileName = "Agent.txt";
    }
    else
    {
        cout << "\nInvalid user role.\n";
        return;
    }

    ifstream file(fileName.c_str());

    if (!file)
    {
        cout << "\nUnable to open profile file.\n";
        return;
    }

    ofstream temp("Profile_temp.txt");

    if (!temp)
    {
        cout << "\nUnable to create temporary file.\n";
        file.close();
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string id;
        string name;
        string phone;
        string email;
        string password;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, password);

        if (id == currentID)
        {
            found = true;

            // Keep ID unchanged
            temp << id << ","
                 << newName << ","
                 << newPhone << ","
                 << newEmail << ","
                 << password << endl;
        }
        else
        {
            // Keep other users unchanged
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    if (!found)
    {
        cout << "\nUser profile not found.\n";
        remove("Profile_temp.txt");
        return;
    }

    // Replace original file
    remove(fileName.c_str());
    rename("Profile_temp.txt", fileName.c_str());

    // Update global variables
    currentName = newName;
    currentPhone = newPhone;
    currentEmail = newEmail;

    cout << "\n========================================\n";
    cout << "       PROFILE UPDATED SUCCESSFULLY\n";
    cout << "========================================\n";

    cout << "ID          : " << currentID << endl;
    cout << "Name        : " << currentName << endl;
    cout << "Phone       : " << currentPhone << endl;
    cout << "Email       : " << currentEmail << endl;
}
