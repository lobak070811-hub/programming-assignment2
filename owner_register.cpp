#include "header.h" 

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct Owner
{
    string id;
    string name;
    string phone;
    string email;
    string password;
};

int defaultOwnerID();
void inputOwner(Owner &ow);
void saveOwner(Owner o);
void array_ownerlist();
void displayOwner(Owner o);

void ownerRegister()//main function
{
    struct Owner o;

    inputOwner(o);

    saveOwner(o);
    
    array_ownerlist();
}

int defaultOwnerID(){
	
    ifstream file("Owner.txt");

    string line;
    int maxID = 0;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string ownerID;

        // Read the first field before comma
        getline(ss, ownerID, ',');

        // Example: S001
        // Remove "S"
        if (ownerID.length() > 1)
        {
            string numberPart = ownerID.substr(1);

            int idNumber = 0;

            stringstream convert(numberPart);
            convert >> idNumber;

            if (idNumber > maxID)
            {
                maxID = idNumber;
            }
        }
    }

    file.close();

    return maxID + 1;
}

void inputOwner(Owner &ow)
{
    Owner o;//Owner

    cout << "Name       : ";
    cin.ignore();
    getline(cin, ow.name);

    cout << "Phone      : ";
    getline(cin, ow.phone);

    cout << "Email      : ";
    getline(cin, ow.email);

    cout << "Password   : ";
    getline(cin, ow.password);

}

void saveOwner(Owner o)
{
    ofstream file("Owner.txt", ios::app);
    
    int id = defaultOwnerID();

    if (file.is_open())
    {
        string ownerID;

        stringstream ss;
		ss << id;
		string number;
		ss >> number;

		if (id < 10)
		{
    		ownerID = "O00" + number;
		}
		else if (id < 100)
		{
    		ownerID = "O0" + number;
		}
		else
		{
    		ownerID = "O" + number;
		}

        file << ownerID << ","
             << o.name << ","
             << o.phone << ","
             << o.email << ","
             << o.password << endl;

        file.close();
        
        o.id = ownerID;
        displayOwner(o);
    }
    else
    {
        cout << "Cannot open file.\n";
    }
    
    system("pause");
}

Owner ownerList[50];
int ownerCount = 0;

void array_ownerlist()
{
	ifstream file("Owner.txt");
	
	if(!file)
	{
		cout << "Cannot open owner.txt" << endl;
		return;
	}

	string line;

	while(getline(file, line))
	{
    	stringstream ss(line);

    	getline(ss, ownerList[ownerCount].id, ',');
    	getline(ss, ownerList[ownerCount].name, ',');
    	getline(ss, ownerList[ownerCount].phone, ',');
    	getline(ss, ownerList[ownerCount].email, ',');
    	getline(ss, ownerList[ownerCount].password);

    	ownerCount++;
	}

	file.close();
}

void displayOwner(Owner o)
{
    cout << "\n============================================\n";
    cout << "          REGISTRATION SUCCESSFUL\n";
    cout << "============================================\n";

    cout << "ID       : " << o.id << endl;
    cout << "Name     : " << o.name << endl;
    cout << "Phone    : " << o.phone << endl;
    cout << "Email    : " << o.email << endl;

    cout << "============================================\n\n";
}
