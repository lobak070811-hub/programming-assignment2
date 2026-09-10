#include "header.h"

#include <iostream>

using namespace std;

void studentMenu()//main function
{
    int choice;

    while (true)
    {
    	system("cls");
        cout << "\n========================================" << endl;
        cout << "              STUDENT MENU" << endl;
        cout << "========================================" << endl;
        

        cout << "Welcome, " << currentName << "!\n";
        cout << "ID    : " << currentID << endl;
        cout << "Phone : " << currentPhone << endl;

        cout << "\n------------------------------------\n";
        cout << "1. View Profile" << endl;
        cout << "2. View Property" << endl;
        cout << "3. Search Property" << endl;
        cout << "4. Add Shortlist" << endl;
        cout << "5. View Shortlist" << endl;
        cout << "6. Send Enquiry" << endl;
        cout << "7. View Reply" << endl;
        cout << "8. Give review to Property" << endl;
        cout << "9. Make appointment" << endl;
        cout << "10. Check Appointment Status" << endl;
        cout << "11. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if(cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "\nInvalid input. Please enter a number.\n";
			continue;
		} 

        switch(choice)
        {
            case 1:
                viewProfile();
                break;
                
            case 2:
            	viewPropertyStudent();
            	break;

            case 3:
                searchProperty();
                break;

            case 4:
                addShortlist();
                break;
                
            case 5:
            	viewShortlistStudent();
            	break;
            	
            case 6:
            	sendEnquiry();
            	break;
            	
            case 7:
            	viewEnquiriesReply();
            	break;
            	
            case 8:
            	giveReview();
            	break;
            	
            case 9:
            	makeAppointment();
            	break;
            	
            case 10:
            	checkAppointmentStatus();
            	break;

            case 11:
                cout << "\nLogging out..." << endl;
                return;

            default:
                cout << "\nInvalid choice. Please try again." << endl;
                break;
        }
    }
}
