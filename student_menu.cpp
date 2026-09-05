#include "header.h"

#include <iostream>

using namespace std;

void studentMenu()//main function
{
    int choice;

    do
    {
        cout << "\n========================================" << endl;
        cout << "              STUDENT MENU" << endl;
        cout << "========================================" << endl;
        cout << "1. View Property" << endl;
        cout << "2. Search Property" << endl;
        cout << "3. Add Shortlist" << endl;
        cout << "4. View Shortlist" << endl;
        cout << "5. Send Enquiry" << endl;
        cout << "6. View Reply" << endl;
        cout << "7. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                viewPropertyStudent();
                break;

            case 2:
                searchProperty();
                break;

            case 3:
                addShortlist();
                break;
                
            case 4:
            	viewShortlistStudent();
            	break;
            	
            case 5:
            	sendEnquiry();
            	break;
            	
            case 6:
            	viewEnquiriesReply();
            	break;

            case 7:
                cout << "\nLogging out..." << endl;
                break;

            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }

    } while(choice != 7);
}
