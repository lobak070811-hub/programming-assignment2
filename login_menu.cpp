#include "header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//define global variable
//temporary storage to save log in details, destroyed after finish editing
string currentID;
string currentName;
string currentPhone;
string currentRole;

void getUserInfo(string filename, string inputID, string &name, string &phone)
{
    ifstream file(filename.c_str());

    if (!file.is_open())
    {
        return;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id;
        string email;
        string password;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, password);

        if (id == inputID)
        {
            file.close();
            return;
        }
    }

    file.close();
}

bool checkLogin(string filename, string inputID, string inputPassword)
{
    ifstream file(filename.c_str());

    if (!file.is_open())
    {
        return false;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id;
        string name;
        string phone;
        string email;
        string password;

        // Read each field from the .txt file
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, password);

        // Check ID and Password
        if (id == inputID && password == inputPassword)
        {
            file.close();
            return true;
        }
    }

    file.close();

    return false;
}

void loginMenu()//main function
{ 
    string inputID;
    string inputPassword;

    cout << "\n=============================\n";
    cout << "           LOG IN\n";
    cout << "=============================\n";

    cout << "ID       : ";
    cin >> inputID;

    cout << "Password : ";
    cin >> inputPassword;

    // Check Student
    if (checkLogin("Student.txt", inputID, inputPassword))
	{
    	currentID = inputID;

    	getUserInfo(
        	"Student.txt",
        	inputID,
        	currentName,
        	currentPhone
    	);

    	currentRole = "Student";

    	cout << "\nLogin Successful!\n";
    	cout << "Welcome, " << currentName << "!\n";
	
    	studentMenu();
		
    	return;
	}

    // Check Owner
	if (checkLogin("Owner.txt", inputID, inputPassword))
	{
    	currentID = inputID;

    	getUserInfo(
        	"Owner.txt",
        	inputID,
        	currentName,
        	currentPhone
    	);

    	currentRole = "Owner";

    	cout << "\nLogin Successful!\n";
    	cout << "Welcome, " << currentName << "!\n";

    	ownerPropertyMenu();

    	return;
	}

    // Check Agent
    if (checkLogin("Agent.txt", inputID, inputPassword))
    {
    	currentID = inputID;

    	getUserInfo(
        	"Agent.txt",
        	inputID,
        	currentName,
        	currentPhone
    	);

    	currentRole = "Agent";
    	
        cout << "\nLogin Successful!\n";
        cout << "Welcome, " << currentName << "!\n";
    	
        agentPropertyMenu();

        return;
    }
    // If no matching ID + Password
    cout << "\nLogin Failed!\n";
    cout << "Incorrect ID or Password.\n";
    
    system("pause");
}
