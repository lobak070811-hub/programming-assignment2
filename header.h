#ifndef MY_HEADER
#define MY_HEADER

#include <iostream>
#include <string>

//declare global variable
extern std::string currentID;
extern std::string currentName;
extern std::string currentPhone;
extern std::string currentRole;

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
void viewProperty();

#endif //end code
