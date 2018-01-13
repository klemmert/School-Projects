// Project3Lemmert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Trie.h"

using namespace std;


int main()
{
	ifstream inFile;
	bool run = true;
	string word = "";
	string response = "";
	string dict = "";
	cout << "Please enter a word prefix (or press enter to exit): ";
	getline(cin, word);
	Trie temp;
	//open file and insert the dictionary
	inFile.open("wordlist.txt");
	if (!inFile) {
		cout << "Unable to open file." << endl;
	}
	else {
		while (inFile >> dict) {
			temp.insert(dict);
		}
	}
	inFile.close();
	//run until user presses enter to exit
	while (run) {
		if ((word.compare("")) == 0) {
			run = false;
		}
		else {
			vector<string> completions = temp.complete(word);
			cout << "There are " << temp.completeCount(word) << " completions for the prefix '" << word << "'. Show completions? ";
			cin >> response;
			//if user wants to see completions, print it out
			if ((response.compare("yes")) == 0) {
				cout << "\nCompletions" << endl;
				cout << "-----------" << endl;
				for (int i = 0; i != completions.size(); ++i) {
					cout << completions[i] << endl;
				}
			}
		cout << "Please enter a word prefix (or press enter to exit): ";
		cin.ignore();
		getline(cin, word);
		}
	}
	
    return 0;
}

