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

struct Enquiry
{
    string enquiryID;
    string studentID;
    string propertyID;
    string publisherID;
    string question;
    string reply;
};

struct Schedule
{
    string scheduleID;
    string publisherID;
    string day;
    string startTime;
    string endTime;
};

struct Appointment
{
    string appointmentID;
    string studentID;
    string publisherID;
    string propertyID;
    string scheduleID;
    string date;
    string day;
    string startTime;
    string endTime;
    string status;
    string reason;
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
void searchProperty();
void viewPropertyStudent();
void addShortlist();
void viewShortlistStudent();

void sendEnquiry();
void viewEnquiriesReply();
void viewEnquiries();
void replyEnquiries();

void giveReview();
void displayPropertyReview(string propertyID);

void editScheduleMenu();
void addSchedule();
void deleteSchedule();
void viewSchedule();

void makeAppointment();
void checkAppointment();
void checkAppointmentStatus();

#endif //end code
