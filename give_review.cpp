#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Review
{
    string reviewID;
    string studentID;
    string propertyID;
    int rating;
    string comment;
};

string defaultReviewID();
bool existsProperty(string propertyID);
void displayPropertyReview(string propertyID);
void givePropertyReview();

void giveReview()//main function
{
	givePropertyReview();
	
	return;
}

string defaultReviewID()
{
    ifstream file("Review.txt");

    string line;
    int maxID = 0;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string reviewID;

        getline(ss, reviewID, '|');

        if (reviewID.length() > 1)
        {
            string numberPart = reviewID.substr(1);

            stringstream numberStream(numberPart);

            int number = 0;

            numberStream >> number;

            if (number > maxID)
                maxID = number;
        }
    }

    file.close();

    maxID++;

    stringstream newID;

    newID << "R";

    if (maxID < 10)
        newID << "00";
    else if (maxID < 100)
        newID << "0";

    newID << maxID;

    return newID.str();
}

bool existsProperty(string propertyID)
{
    ifstream file("Property.txt");

    if (!file)
        return false;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string id;

        getline(ss, id, ',');

        if (id == propertyID)
        {
            file.close();
            return true;
        }
    }

    file.close();

    return false;
}

void displayPropertyReview(string propertyID)
{
    ifstream file("Review.txt");

    if (!file)
    {
        cout << "\nNo review available.\n";
        return;
    }

    string line;

    int reviewCount = 0;

    int totalRating = 0;

    cout << "\n----------------------------------------\n";
    cout << "Property Reviews\n";
    cout << "----------------------------------------\n";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        Review r;

        string ratingString;

        getline(ss, r.reviewID, '|');
        getline(ss, r.studentID, '|');
        getline(ss, r.propertyID, '|');
        getline(ss, ratingString, '|');
        getline(ss, r.comment);

        stringstream ratingStream(ratingString);

        ratingStream >> r.rating;

        // Only display reviews for this property
        if (r.propertyID == propertyID)
        {
            cout << "\nReview ID : " << r.reviewID;
            cout << "\nRating    : " << r.rating << " / 5";
            cout << "\nComment   : " << r.comment;
            cout << "\n";

            reviewCount++;

            totalRating += r.rating;
        }
    }

    file.close();

    if (reviewCount == 0)
    {
        cout << "\nNo review for this property yet.\n";
    }
    else
    {
        double averageRating;

        averageRating = (double)totalRating / reviewCount;

        cout << "\n----------------------------------------\n";
        cout << "Total Reviews  : " << reviewCount;
        cout << "\nAverage Rating  : "
             << fixed << setprecision(1)
             << averageRating << " / 5";
        cout << "\n----------------------------------------\n";
    }
}

void givePropertyReview()
{
    string propertyID;

    cout << "\n========================================\n";
    cout << "Give Property Review\n";
    cout << "========================================\n";

    cout << "Student ID : " << currentID << endl;

    cout << "\nEnter Property ID: ";
    cin >> propertyID;

    // Check property
    if (!existsProperty(propertyID))
    {
        cout << "\nProperty ID does not exist.\n";
        
        system("pause");
        return;
    }

    int rating;

    cout << "\nEnter rating (1 - 5): ";
    cin >> rating;

    // Validate rating, prevent character entered
    while (rating < 1 || rating > 5)
    {
        cout << "Invalid rating. Please enter 1 - 5: ";
        cin >> rating;
    }

    cin.ignore();

    string comment;

    cout << "Enter your review: ";
    getline(cin, comment);

    if (comment.empty())
    {
        cout << "\nReview cannot be empty.\n";
        
        system("pause");
        return;
    }

    Review r;

    r.reviewID = defaultReviewID();

    r.studentID = currentID;

    r.propertyID = propertyID;

    r.rating = rating;

    r.comment = comment;

    // Save Review
    ofstream file("Review.txt", ios::app);

    if (!file)
    {
        cout << "\nUnable to open Review.txt.\n";
        return;
    }

    file << r.reviewID << "|"
         << r.studentID << "|"
         << r.propertyID << "|"
         << r.rating << "|"
         << r.comment << endl;

    file.close();

    cout << "\n========================================\n";
    cout << "Review submitted successfully!\n";
    cout << "========================================\n";

    cout << "\nReview ID : " << r.reviewID;
    cout << "\nProperty ID : " << r.propertyID;
    cout << "\nRating : " << r.rating << " / 5";
    cout << "\nComment : " << r.comment << endl;
    
    system("pause");
}
