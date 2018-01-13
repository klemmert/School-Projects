
#include "stdafx.h"
#include <iostream>
#include "MagicBag.h"

#define MB_CHECK_SIZE 100
#define NUM_MEM_TESTS 100000

using namespace std;

void memoryLeakTest();

int main() {

	MagicBag <int> mb1;

	//change this to a ridiculously large number to make sure it still works
	for (int i = 0; i < MB_CHECK_SIZE; i++) {
		mb1.insert(i);
		mb1.insert(111);
	}

	cout << "Printing an integer bag:" << endl;
	mb1.print(cout);

	int d = mb1.draw();

	cout << "What I drew from mb1:" << endl;
	cout << d << endl << endl;

	cout << "Should be missing " << d << endl;
	mb1.print(cout);

	MagicBag <int> mb3;
	mb3 = mb1;
	d = mb1.draw();

	cout << "Should be missing " << d << endl;
	mb1.print(cout);

	cout << "mb3 Should not be missing " << d << endl;
	mb3.print(cout);

	cout << "Testing peek, how many 111s we got?" << endl;
	cout << mb1.peek(111) << endl << endl;
	cout << "Should not be missing ^" << endl;
	mb1.print(cout);

	cout << "Making a large character bag..." << endl;
	MagicBag <char> mb4;
	for (int i = 0; i < 1000; i++) {
		mb4.insert('a');
	}

	cout << "Making a large bag of doubles..." << endl;
	MagicBag <double> mb5;
	for (int i = 0; i < 1000; i++) {
		mb5.insert(1.0);
	}

	cout << "Start memory leak test:" << endl;
	for (int i = 0; i < NUM_MEM_TESTS; i++) {
		memoryLeakTest();
	}
	cout << "End memory leak test" << endl;

	system("pause");

	return 0;
}


void memoryLeakTest() {
	MagicBag <int> mb7;
	for (int i = 0; i < MB_CHECK_SIZE; i++) {
		mb7.insert(i);
	}
	MagicBag<int> mb9;
	mb9 = mb7;
}