#include "header.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string searchPropertyID;
bool propertyFound = false;
Property updatedProperty;
vector<Property> properties;

void inputPropertyID(); 
bool readProperties(); 
void updateProperty(); 
void saveProperties(); 
void displayUpdatedProperty();

void renewProperty()//main function
{ 
	propertyFound = false; 
	 
	inputPropertyID(); 
	
	if (!readProperties()) 
	{ 
		return; 
	} 
	
	updateProperty(); 
	 
	if (!propertyFound) 
	{ 
		return; 
	} 
	
	saveProperties(); 
	
	displayUpdatedProperty(); 
}

void inputPropertyID() 
{ 
	cout << "\n=============================\n"; 
	cout << " EDIT PROPERTY\n"; 
	cout << "=============================\n"; 
	
	cout << "Enter Property ID: "; 
	cin >> searchPropertyID;
}

bool readProperties() 
{ 
	ifstream file("Property.txt"); 
	if (!file) 
	{ 
		cout << "\nCannot open Property.txt\n"; 
		return false; 
	} 
	properties.clear(); 
	string line; 
	while (getline(file, line)) 
	{ 
		if (line.empty()) 
		{ 
			continue; 
		} 
		
		stringstream ss(line); 
		Property p;
		
		getline(ss, p.propertyID, ','); 
		getline(ss, p.roomType, ',');  
		getline(ss, p.propertyName, ',');  
		getline(ss, p.location, ','); 
		 
		string price; 
		string area; 
		string distance;
		
		getline(ss, price, ','); 
		getline(ss, area, ','); 
		getline(ss, distance, ','); 
		 
		stringstream priceStream(price);// Convert string to double
		priceStream >> p.price; 
		stringstream areaStream(area); 
		areaStream >> p.area; 
		stringstream distanceStream(distance); 
		distanceStream >> p.distance; 
		 
		getline(ss, p.publisherID, ',');// Read Publisher Information 
		getline(ss, p.publisherName, ','); 
		getline(ss, p.publisherPhone, ','); 
		getline(ss, p.publisherRole); 
		 
		if (p.propertyID == searchPropertyID && p.publisherID == currentID)
		{ 
			propertyFound = true; 
			updatedProperty = p; 
		}  
		properties.push_back(p); // Save every property into vector
	} 
		file.close(); 
		
		return true; 
}

void updateProperty() 
{ 
	if (!propertyFound) 
	{ 
		cout << "\nProperty not found.\n"; 
		return; 
	} 
	
	cout << "\nProperty found!\n"; 
	cin.ignore();
	
	cout << "\nNew Property Name : "; 
	getline(cin, updatedProperty.propertyName); 
 
	cout << "New Location : "; 
	getline(cin, updatedProperty.location); 
	 
	cout << "New Price (RM) : "; 
	cin >> updatedProperty.price; 
	
	cout << "New Area (sqft) : "; 
	cin >> updatedProperty.area; 
	 
	cout << "New Distance (km) : "; 
	cin >> updatedProperty.distance; 
	
	for (int i = 0; i < properties.size(); i++)// Update the property inside vector
	{ 
		if (properties[i].propertyID == searchPropertyID && properties[i].publisherID == currentID)
		{ 
			properties[i] = updatedProperty; 
			break; 
		} 
	} 
}

void saveProperties() 
{ 
	ofstream outFile("Property.txt"); 
	
	if (!outFile) 
	{ 
		cout << "\nCannot open Property.txt for writing.\n"; 
		return; 
	}
	
	for (int i = 0; i < properties.size(); i++) 
	{ 
		outFile << properties[i].propertyID << "," 
		<< properties[i].roomType << "," 
		<< properties[i].propertyName << "," 
		<< properties[i].location << "," 
		<< properties[i].price << "," 
		<< properties[i].area << "," 
		<< properties[i].distance << "," 
		<< properties[i].publisherID << "," 
		<< properties[i].publisherName << "," 
		<< properties[i].publisherPhone << "," 
		<< properties[i].publisherRole 
		<< endl; 
	} 
	
	outFile.close();
}

void displayUpdatedProperty() 
{ 
	cout << "\n=====================================\n"; 
	cout << " PROPERTY UPDATE SUCCESSFULLY\n"; 
	cout << "=====================================\n";
	
	cout << "Property ID    : " << updatedProperty.propertyID << endl; 
	cout << "Room Type      : " << updatedProperty.roomType << endl; 
	cout << "Property Name  : " << updatedProperty.propertyName << endl; 
	cout << "Location       : " << updatedProperty.location << endl; 
	cout << "Price          : RM" << updatedProperty.price << endl; 
	cout << "Area           : " << updatedProperty.area << " sqft" << endl; 
	cout << "Distance       : " << updatedProperty.distance << " km" << endl; 
	cout << "Published By   : " << updatedProperty.publisherName << endl; 
	cout << "Role           : " << updatedProperty.publisherRole << endl; 
	cout << "Phone          : " << updatedProperty.publisherPhone << endl;
	
	cout << "====================================\n"; 
}
