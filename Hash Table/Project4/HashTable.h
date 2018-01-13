#pragma once
#include "Slot.h"
#include <iostream>
#define MAXHASH 1000

using namespace std;

template <class T> class HashTable
{
public:
	Slot<T>* records;
	int recordCount = 0;

	HashTable<T>::HashTable()
	{
		records = new Slot<T>[MAXHASH];
	}

	HashTable<T>::~HashTable()
	{
		delete[] records;
	}
	//inserts into the table and will return false if table is full or if there is a duplicate
	bool HashTable<T>::insert(int key, T value, int & collisions)
	{
		int tempHash = hash(key);
		int tempProbe = probe(key);
		int count = 0;

		while (records[tempHash].isNormal()) {
			count++;
			collisions++;
			//if table is full
			if (checkHash() == false) {
				cout << "Hash is full." << endl;
				return false;
			}
			//if duplicate
			if (records[tempHash].getKey() == key) {
				cout << "Duplicate. Cannot inset this record." << endl;
				return false;
			}
			tempHash = (tempHash + tempProbe) % MAXHASH;
		}
		collisions = count;
		Slot <int> temp(key, value);
		records[tempHash] = temp;
		recordCount++;
		return true;
	}

	//makes a slot a tombstone
	bool HashTable<T>::remove(int key)
	{
		for (int i = 0; i < MAXHASH; i++) {
			if (records[i].getKey() == key) {
				records[i].kill();
				recordCount--;
				return true;
			}
		}
		return false;
	}

	//finds in the hash table and also gives the index
	bool HashTable<T>::find(int key, T & value)
	{
		int tempHash = hash(key);
		int tempProbe = probe(key);
		//iterate through hash table
		while (records[tempHash].isNormal()) {
			if (records[tempHash].getKey() == key) {
				value = records[tempHash].getValue();
				return true;
			}
			tempHash = (tempHash + tempProbe) % MAXHASH;
		}
		return false;
	}

	float HashTable<T>::alpha()
	{
		return (float)recordCount / MAXHASH;
	}

	//borrowed some of the code from https://simpledevcode.wordpress.com/2015/07/07/hash-tables-tutorial-c-c-java/
	bool HashTable<T>::checkHash()
	{
		bool space = false;
		for (int i = 0; i < MAXHASH; i++) {
			if (records[i].isNormal() == 1) {
				space = true;
			}
		}
		return space;
	}

	//makes the probe
	int HashTable<T>::probe(int key) {
		return (key * MAXHASH - 1) % MAXHASH;
	}
	
	//makes the hash (double hashing)
	int HashTable<T>::hash(int key)
	{
		return key % MAXHASH;
	}

	//doesn't work
	friend ostream& operator<<(ostream& os, const HashTable& get) {
		return os;
	}
};

