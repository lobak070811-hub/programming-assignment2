//agent registeration
#include "header.h" 

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct Agent
{
    string id;
    string name;
    string phone;
    string email;
    string password;
};

int defaultAgentID();
void inputAgent(Agent &ag);
void saveAgent(Agent a);
void array_agentlist();
void displayAgent(Agent a);

void agentRegister()//main function
{
    struct Agent a;

    inputAgent(a);

    saveAgent(a);
    
    array_agentlist();
}

int defaultAgentID()
{	
    ifstream file("Agent.txt");

    string line;
    int maxID = 0;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string agentID;

        // Read the first field before comma
        getline(ss, agentID, ',');

        // Example: S001
        // Remove "S"
        if (agentID.length() > 1)
        {
            string numberPart = agentID.substr(1);

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

void inputAgent(Agent &ag)
{
    Agent a;//Owner

    cout << "Name       : ";
    cin.ignore();
    getline(cin, ag.name);

    cout << "Phone      : ";
    getline(cin, ag.phone);

    cout << "Email      : ";
    getline(cin, ag.email);

    cout << "Password   : ";
    getline(cin, ag.password);

}

void saveAgent(Agent a)
{
    ofstream file("Agent.txt", ios::app);
    
    int id = defaultAgentID();

    if (file.is_open())
    {
        string agentID;

        stringstream ss;
		ss << id;
		string number;
		ss >> number;

		if (id < 10)
		{
    		agentID = "A00" + number;
		}
		else if (id < 100)
		{
    		agentID = "A0" + number;
		}
		else
		{
    		agentID = "A" + number;
		}

        file << agentID << ","
             << a.name << ","
             << a.phone << ","
             << a.email << ","
             << a.password << endl;

        file.close();
        
        a.id = agentID;
        displayAgent(a);
    }
    else
    {
        cout << "Cannot open file.\n";
    }
}

Agent agentList[50];
int agentCount = 0;

void array_agentlist()
{
	ifstream file("Agent.txt");
	
	if(!file)
	{
		cout << "Cannot open agent.txt" << endl;
		return;
	}

	string line;

	while(getline(file, line))
	{
    	stringstream ss(line);

    	getline(ss, agentList[agentCount].id, ',');
    	getline(ss, agentList[agentCount].name, ',');
    	getline(ss, agentList[agentCount].phone, ',');
    	getline(ss, agentList[agentCount].email, ',');
    	getline(ss, agentList[agentCount].password);

    	agentCount++;
	}

	file.close();
}

void displayAgent(Agent a)
{
    cout << "\n============================================\n";
    cout << "          REGISTRATION SUCCESSFUL\n";
    cout << "============================================\n";

    cout << "ID       : " << a.id << endl;
    cout << "Name     : " << a.name << endl;
    cout << "Phone    : " << a.phone << endl;
    cout << "Email    : " << a.email << endl;

    cout << "============================================\n";
}
