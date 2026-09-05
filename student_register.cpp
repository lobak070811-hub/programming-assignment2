#include "header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct Student
{
    string id;
    string name;
    string phone;
    string email;
    string password;
};

int defaultStudentID();
void inputStudent(Student &stu);
void saveStudent(Student s);
void arraystudentlist();
void displayStudent(Student s);

void studentRegister()//main function
{
    struct Student s;

    inputStudent(s);

    saveStudent(s);
    
    arraystudentlist();
}

int defaultStudentID()
{	
    ifstream file("Student.txt");

    string line;
    int maxID = 0;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string studentID;

        // Read the first field before comma
        getline(ss, studentID, ',');

        // Example: S001
        // Remove "S"
        if (studentID.length() > 1)
        {
            string numberPart = studentID.substr(1);

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

void inputStudent(Student &stu)
{
    Student s;//Student

    cout << "Name       : ";
    cin.ignore();
    getline(cin, stu.name);

    cout << "Phone      : ";
    getline(cin, stu.phone);

    cout << "Email      : ";
    getline(cin, stu.email);

    cout << "Password   : ";
    getline(cin, stu.password);

}

void saveStudent(Student s)
{
    ofstream file("Student.txt", ios::app);
    
    int id = defaultStudentID();

    if (file.is_open())
    {
        string studentID;

        stringstream ss;
		ss << id;
		string number;
		ss >> number;

		if (id < 10)
		{
    		studentID = "S00" + number;
		}
		else if (id < 100)
		{
    		studentID = "S0" + number;
		}
		else
		{
    		studentID = "S" + number;
		}

        file << studentID << ","
             << s.name << ","
             << s.phone << ","
             << s.email << ","
             << s.password << endl;

        file.close();
        
        s.id = studentID;
        displayStudent(s);
    }
    else
    {
        cout << "Cannot open file.\n";
    }
    
    system("pause");
}

Student studentList[100];
int studentCount = 0;

void arraystudentlist()
{
	ifstream file("Student.txt");
	
	if(!file)
	{
		cout << "Cannot open student.txt" << endl;
		return;
	}

	string line;

	while(getline(file, line))
	{
    	stringstream ss(line);

    	getline(ss, studentList[studentCount].id, ',');
    	getline(ss, studentList[studentCount].name, ',');
    	getline(ss, studentList[studentCount].phone, ',');
    	getline(ss, studentList[studentCount].email, ',');
    	getline(ss, studentList[studentCount].password);

    	studentCount++;
	}

	file.close();
}

void displayStudent(Student s)
{
    cout << "\n============================================\n";
    cout << "          REGISTRATION SUCCESSFUL\n";
    cout << "============================================\n";

    cout << "ID       : " << s.id << endl;
    cout << "Name     : " << s.name << endl;
    cout << "Phone    : " << s.phone << endl;
    cout << "Email    : " << s.email << endl;

    cout << "============================================\n\n";
}
