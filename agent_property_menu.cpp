#include "header.h"

#include <iostream>

using namespace std;

void agentPropertyMenu()
{
    int choice;

    while (true)
    {
    	system("cls");
        cout << "\n====================================\n";
        cout << "              AGENT MENU\n";
        cout << "====================================\n";

        cout << "Welcome, " << currentName << "!\n";
        cout << "ID    : " << currentID << endl;
        cout << "Phone : " << currentPhone << endl;

        cout << "\n------------------------------------\n";
        cout << "1. View Profile\n";
        cout << "2. Upload Property\n";
        cout << "3. Edit Property\n";
        cout << "4. Delete Property\n";
        cout << "5. View My Properties\n";
        cout << "6. View Average Price of Properties\n";
        cout << "7. View Enquiries\n";
        cout << "8. Reply Enquiries\n";
        cout << "9. Edit house viewing schedules\n";
        cout << "10. Check appointment\n";
        cout << "11. Log out\n";
        cout << "------------------------------------\n";

        cout << "Enter your choice: ";
        cin >> choice;
        
        if(cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "\nInvalid input. Please enter a number.\n";
			continue;
		} 

        switch (choice)
        {
            case 1:
                viewProfile();
                break;
                
            case 2:
            	addProperty();
            	break;

            case 3:
                renewProperty();
                break;

            case 4:
                deleteProperty();
                break;

            case 5:
                viewPropertyPublisher();
                break;
                
            case 6:
            	viewAveragePrice();
            	break;
                
            case 7:
            	viewEnquiries();
            	break;
            	
            case 8:
            	replyEnquiries();
            	break;
            	
            case 9:
            	editScheduleMenu();
            	break;
            	
            case 10:
            	checkAppointment();
            	break;

            case 11:
                cout << "\nLogging out...\n";

                currentID = "";
                currentName = "";
                currentPhone = "";
                currentRole = "";

                return;

            default:
                cout << "\nInvalid choice.\n";
                break;
        }
    }
}
