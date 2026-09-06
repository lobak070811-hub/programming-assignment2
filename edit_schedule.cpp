#include "header.h"

#include <iostream>

using namespace std;

void editSchedule()
{
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "             EDIT SCHEDULE\n";
        cout << "========================================\n";

        cout << "Publisher ID : " << currentID << endl;

        cout << "\n1. Add Schedule";
        cout << "\n2. Delete Schedule";
        cout << "\n3. View Schedule";
        cout << "\n4. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addSchedule();
                break;

            case 2:
                deleteSchedule();
                break;

            case 3:
                viewSchedule();
                break;

            case 4:
                cout << "\nReturning to previous menu...\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (choice != 4);
}
