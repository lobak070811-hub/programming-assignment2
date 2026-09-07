#include "header.h"

#include <iostream>

using namespace std;

void viewProfile()
{
    char choice;

    cout << "\n========================================\n";
    cout << "             VIEW PROFILE\n";
    cout << "========================================\n";

    cout << "ID          : " << currentID << endl;
    cout << "Name        : " << currentName << endl;
    cout << "Phone       : " << currentPhone << endl;
    cout << "Email       : " << currentEmail << endl;
    cout << "Role        : " << currentRole << endl;

    cout << "========================================\n";

    do
    {
        cout << "\nDo you want to edit your profile? (Y/N): ";
        cin >> choice;

        if (choice != 'Y' && choice != 'y' &&
            choice != 'N' && choice != 'n')
        {
            cout << "Please enter Y or N.\n";
        }

    } while (choice != 'Y' && choice != 'y' &&
             choice != 'N' && choice != 'n');

    if (choice == 'Y' || choice == 'y')
    {
        editProfile();
    }
}
