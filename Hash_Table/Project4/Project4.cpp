// Project4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Records.h"
#include "HashTable.h"

using namespace std;

int main()
{
	Records <int> student;
	HashTable <int> hash;
	string input;
	string firstName;
	string lastName;
	string major;
	int uid;
	string year;
	int index;
	//don't think I did this right so it's probably not going to be used like it should be :(
	int collisions;

	cout << "Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (Q)uit?" << endl;
	cout << "Enter action: ";
	cin >> input;

	//until user hits Q
	while (input.compare("Q") != 0) {
		if (input.compare("I") == 0) {
			//get data
			cout << "Inserting a new record." << endl;
			cout << "Last name: ";
			cin >> lastName;
			cout << "First name: ";
			cin >> firstName;
			cout << "UID: ";
			cin >> uid;
			cout << "Major: ";
			cin >> major;
			cout << "Year: ";
			cin >> year;
			//insert into linked list
			student.insert(lastName, firstName, uid, major, year);
			index = student.find(uid);
			//insert into hash
			bool worked = hash.insert(uid, index, collisions);
			if (worked == true) {
				cout << "Record inserted." << endl;
			}
		}
		else if (input.compare("D") == 0) {
			cout << "Enter UID to delete: ";
			cin >> uid;
			//find index of node wanting to be deleted to delete from linked list
			hash.find(uid, index);
			bool deleted = hash.remove(uid);
			if (deleted == true) {
				//delete from linked list
				student.deleteNode(index);
			}
			else {
				cout << "Error: Record could not be delete." << endl;
			}
		}
		else if (input.compare("S") == 0) {
			cout << "Enter UID to search for: ";
			cin >> uid;

			cout << "Searching... ";
			bool found = hash.find(uid, index);
			if (found == true) {
				cout << "Record found." << endl;
				student.print(cout, index);
			}
			else {
				cout << "Record not found" << endl;
			}
		}

		cout << "Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (Q)uit?" << endl;
		cout << "Enter action: ";
		cin >> input;
	}

	system("pause");
	return 0;
}
