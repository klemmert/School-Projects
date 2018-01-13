#pragma once
#include <string>

using namespace std;

template <class T> class Records
{
public:
	class Node {
	public:
		string last;
		string first;
		int UID;
		string major;
		string year;
		int index;

		Node* next;

		Node() {
			next = nullptr;
		}
	};

	//constructor
	Records() {
		last = "";
		first = "";
		UID = 0;
		major = "";
		year = "";
		head = nullptr;
	}

	//deconstructor
	~Records() {
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

	//inserts into linked list
	void insert(string lastName, string firstName, int userID, string studentMajor, string studentYear) {
		Node * current;
		Node * newNode = new Node();
		newNode->last = lastName;
		newNode->first = firstName;
		newNode->UID = userID;
		newNode->major = studentMajor;
		newNode->year = studentYear;

		if (!head) {
			count++;
			newNode->index = count;
			head = newNode;
		}
		else {
			if (find(newNode->UID) == 0) {
				current = head;
				while (current->next) {
					current = current->next;
				}
				count++;
				newNode->index = count;
				current->next = newNode;
			}
		}
	}

	//find the node that has the same uid and return the index
	int find(int uid) {
		Node * current = head;
		if (!head) {
			return 0;
		}
		else {
			while (current) {
				if (current->UID == uid) {
					return current->index;
				}
				current = current->next;
			}
		}
		return 0;
	}

	//deletes node based on index
	void deleteNode(int index) {
		Node * current = head;
		Node * prev = head;
		int keepCount = 0;

		//if head is removed
		if (index == 0) {
			head = current->next;
			free(current);
			return;
		}

		//start before the node that will be deleted
		while (current->next) {
			if (keepCount == index - 1) {
				Node * temp = current->next->next;
				free(current->next);
				current->next = temp;
				break;
			}
			else {
				keepCount++;
				current = current->next;
			}
		}
	}

	//prints selected node
	ostream& print(ostream& os, int index) const {
		Node * current = head;
		while (current) {
			if (current->index == index) {
					os << "---------------------" << endl;
					os << "Last Name: " << current->last << endl;
					os << "First Name: " << current->first << endl;
					os << "UID: " << current->UID << endl;
					os << "Year: " << current->year << endl;
					os << "Major: " << current->major << endl;
					os << "---------------------" << endl;
					return os;
			}
			current = current->next;
		}
		return os;
	}

private:
	string last;
	string first;
	int UID;
	string major;
	string year;
	int count = 0;;
	Node *head;
};

