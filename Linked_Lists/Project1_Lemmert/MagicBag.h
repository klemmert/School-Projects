#pragma once

#include <iostream>
//used for rand()
#include <time.h>
#include <stdlib.h>

using namespace std;

//make sure to use javadocs to document well for program
template<class T> class MagicBag
{
public:

	//nested class for linked list nodes
	class Node {
	public:
		//add in what should the node be pointing to
		T item;
		Node* next; //ptr to the item

		Node() {
			next = nullptr; //initialize it nullptr
		}
	};

	//default parameter
	MagicBag() {
		item = 0;
		head = nullptr;
	}

	//parameterized constructure
	MagicBag(const MagicBag& other) {
		item = other;
		head = nullptr;
	}

	//this is returning a student reference (the this pointer)
	MagicBag& operator=(const MagicBag& copy) {
		Node * current;
		//overwrite student object
		this->~MagicBag();
		item = copy.item;

		if (copy.head) {
			current = copy.head;
			while (current) {
				insert(current->item);
				current = current->next;
			}
		}
		return *this;
	}

	//deconstructor
	~MagicBag() {
		Node * destroy;
		Node * destroyNext;
		if (head) {
			destroy = head;
			destroyNext = head->next;

			delete(destroy);
			while (destroyNext) {
				destroy = destroyNext;
				destroyNext = destroyNext->next;
				delete destroy;
			}
		}
		head = nullptr;
	}

	//insert any number of items, duplicates are allowed
	//DONE AND TESTED :)
	void insert(T newItem) {
		Node * newNode;
		Node * current;
		newNode = new Node();
		newNode->item = newItem;

		if (!head) {
			head = newNode;
		}
		else {
			current = head;
			while (current->next) {
				current = current->next;
			}
			current->next = newNode;
		}
	}

	//objects are removed from bag, function returns a random number and
	//removes it from bag. Item should be randomized. If bag is empty,
	//function should throw and exception
	//DONE AND TESTED :)
	T draw() throw(){
		Node * newNode;
		Node * current;
		T value;
		newNode = new Node();
		int iterate = 0; //set count back to 0 to count iteration

		try {
			if (!head) {
				throw exception("Magic bag is empty");
			}
			else {
				int count = getCount(); //use count to find how many are in list
				srand(time(NULL));
				int randomIndex = rand() % count;
				current = head;
				while (current->next) {
					if (iterate == randomIndex) {
						value = current->item;
						deleteNode(randomIndex);
						return (value);
					}
					iterate++;
					current = current->next;
				}
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}

	//helper function for draw to delete node at specific position
	void deleteNode(int index) {
		Node * current = head;
		Node * prev = head;
		int count = 0;

		//if head is removed
		if (index == 0) {
			head = current->next;
			free(current);
			return;
		}

		//start before the node that will be deleted
		while (current->next) {
			if (count == index-1) {
				Node * temp = current->next->next;
				free(current->next);
				current->next = temp;
				break;
			}
			else {
				count++;
				current = current->next;
			}
		}
	}

	//helper function for draw
	int getCount() {
		Node * newNode;
		Node * current;
		newNode = new Node();
		int count = 0;

		if (!head) {
			return 0;
		}
		else {
			current = head;
			while (current->next) {
				count++;
				current = current->next;
			}
		}
		return count;
	}

	//check to see if an object is in the bag, return 0 if there are no items matching
	//the item paramenter. If there are items matching, the number (count) of
	//matching items should be returned
	//DONE AND TESTED
	int peek(T findItem) {
		Node * newNode;
		Node * current;
		newNode = new Node();
		newNode->item = findItem;
		int count = 1;

		if (!head) {
			return 0;
		}
		else {
			current = head;
			while (current->next) {
				if (current->item == findItem) {
					count++;
				}
				current = current->next;
			}
		}
		return count;
	}

	//print with cout in param
	//DONE AND TESTED :)
	ostream& print(ostream& os) const {
		Node * current = head;
		if (current) {
			os << "Magic Bag: " << endl;
			os << current->item;
			current = current->next;
			while (current) {
				os << ", " << current->item;
				current = current->next;
			}
		}
		os << endl;
		return os;
	}

private:
	T item;
	Node * head;
};
