#ifndef MY_HEADER
#define MY_HEADER

#include <iostream>
#include <string>

using namespace std;

//declare global variable
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

extern string currentID;
extern string currentName;
extern string currentPhone;
extern string currentRole;

//declare function
void mainMenu();

void registerMenu();
void studentRegister();
void ownerRegister();
void agentRegister();

void loginMenu();

void ownerPropertyMenu();
void agentPropertyMenu();
void addProperty();
void renewProperty();
void deleteProperty();
void viewPropertyPublisher();

void studentMenu();
void viewPropertyStudent();
void addShortlist();
void viewShortlistStudent();

#endif //end code
