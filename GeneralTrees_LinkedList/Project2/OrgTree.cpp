#include "stdafx.h"
#include "OrgTree.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL

//this tree is a binary general tree
OrgTree::OrgTree()
{
	root = TREENULLPTR;
}


OrgTree::~OrgTree()
{
	destroy(getRoot());
}

void OrgTree::destroy(TREENODEPTR node)
{
	if (node) {
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
}

//create a root node for the tree. If root exists, tree becomes a subtree to new root
//this function would be theta(1)
void OrgTree::addRoot(string title, string name)
{
	TREENODEPTR temp;
	if (root == TREENULLPTR) {
		root = new TreeNode(title, name);
	}
	else {
		temp = new TreeNode(title, name); //create temp holder for new root
		temp->left = root; //move root's data in left child
		root->parent = temp; //move temp location to the top of tree
		root = temp; //make temp data as root data
	}
	size++;
}

//finds size of tree
//this function is theta(1)
unsigned int OrgTree::getSize()
{
	return size;
}

//returns a pointer to root node
//this function is theta(1)
TREENODEPTR OrgTree::getRoot()
{
	return root;
}

//returns left child and if null, null ptr is returned
//this function is theta(1)
TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node)
{
	if (node->left == TREENULLPTR) {
		return TREENULLPTR;
	}
	else {
		return node->left;
	}
}

//returns right sibling and if null, null ptr is returned
//this function is theta(1)
TREENODEPTR OrgTree::rightSibling(TREENODEPTR node)
{
	if (node->right == TREENULLPTR) {
		return TREENULLPTR;
	}
	else {
		return node->right;
	}
}

//prints out subtree starting at a specified node
//this uses recursion, function is theta(1)
//mostly prints correctly but not when node is a specific position
void OrgTree::printSubTree(TREENODEPTR subTreeRoot)
{
	TREENODEPTR temp = subTreeRoot;
	if (subTreeRoot != TREENULLPTR) {
		cout << subTreeRoot->title << ": " << subTreeRoot->name << endl;
		if (subTreeRoot->left != TREENULLPTR) {
			cout << "\t";
			temp = subTreeRoot->left;
			if (temp->left != TREENULLPTR) {
				cout << temp->title << ": " << temp->name << endl;
				cout << "\t\t";
				printSubTree(temp->left);
				cout << "\t";
				printSubTree(subTreeRoot->left->right);
			}
			else {
				//tab if needed
				if (subTreeRoot->parent != root->left && subTreeRoot != root) {
					cout << "\t";
				}
				printSubTree(subTreeRoot->left);
			}
		}
		else if (subTreeRoot->right != TREENULLPTR) {
			cout << "\t\t";
			printSubTree(subTreeRoot->right);
		}
	}
}

TREENODEPTR OrgTree::find(string titleSearch)
{
	TREENODEPTR temp = getRoot();
	return findHelper(titleSearch, temp);
}

//this function finds the node that matches the title, doesn't return parent node though
//this function is theta(1)
TREENODEPTR OrgTree::findHelper(string titleSearch, TREENODEPTR node)
{
	if (node == TREENULLPTR) {
		return TREENULLPTR;
	}
	if (node->title == titleSearch) {
		return node;
	}
	else {
		if (node->left != TREENULLPTR) {
			if(findHelper(titleSearch, node->left) != TREENULLPTR){
				node = findHelper(titleSearch, node->left);
			}
		}

		if (node == TREENULLPTR) {
			return TREENULLPTR;
		}
		if (node->title == titleSearch) {
			return node;
		}
		else {
			if (node->right != TREENULLPTR) {
				if (findHelper(titleSearch, node->right) != TREENULLPTR) {
					node = findHelper(titleSearch, node->right);
				}
			}
			if (node->title == titleSearch) {
				return node;
			}
		}
	}
	return TREENULLPTR;
}

//hire an employee, employees should be added to the tree as the last node pointed to by TREENODEPTR
//this function is theta(n) best case, theta(n log n) worst case
void OrgTree::hire(TREENODEPTR node, string newTitle, string newName)
{
	//if given a node that doesn't exist, or is null
	if (node == TREENULLPTR) {
		cout << "Error. Hiring process was not sent to the proper place." << endl;
	}
	//these are for specified positions
	if (node != root) {
		if (node->left == TREENULLPTR && node->right == TREENULLPTR) {
			node->right = new TreeNode(newTitle, newName);
			size++;
		}
		else if (node->left == TREENULLPTR && node->right != TREENULLPTR) {
			node->left = new TreeNode(newTitle, newName);
			size++;
		}
		else if (node->left != TREENULLPTR && node->right == TREENULLPTR) {
			node->right = new TreeNode(newTitle, newName);
			size++;
		}
	}
	else {
		while (node) {
			if (node->left == TREENULLPTR) {
				node->left = new TreeNode(newTitle, newName);
				size++;
				break;
			}
			else {
				node = node->left;
			}
		}
	}
}

//fires the employee and all employees under the fired one is now working for the boss. If you can't match, return false, and return true when you
//have fired someone properly. This function is theta(n)
bool OrgTree::fire(string formerTitle)
{
	TREENODEPTR temp = root;
	TREENODEPTR tempParent = TREENULLPTR;
	TREENODEPTR kill = TREENULLPTR;

	//go to specific position of who is being fired, also save parent of who's being fired
	tempParent = findParent(formerTitle, temp, tempParent);
	temp = findHelper(formerTitle, temp);
	temp->parent = tempParent;
	if (temp->title == formerTitle) {
		if (temp == root) {
			return false;
		}
		//cases to make sure the nodes beneath the one gets fired is placed correctly in the tree
		if (temp->left != TREENULLPTR && temp->right != TREENULLPTR) {
			kill = temp;
			temp = temp->right;
			temp->parent = tempParent;
			temp->left = kill->left;
			if (tempParent->left->title == kill->title) {
				tempParent->left = temp;
			}
			else if (tempParent->right->title == kill->title) {
				tempParent->right = temp;
			}
			delete(kill);
			kill = TREENULLPTR;
		}
		else if (temp->left != TREENULLPTR && temp->right == TREENULLPTR) {
			kill = temp;
			temp = temp->left;
			temp->parent = tempParent;
			if (tempParent->left->title == kill->title) {
				tempParent->left = temp;
			}
			else if (tempParent->right->title == kill->title) {
				tempParent->right = temp;
			}
			delete(kill);
			kill = TREENULLPTR;
		}
		else if (temp->left == TREENULLPTR && temp->right != TREENULLPTR) {
			kill = temp;
			temp = temp->right;
			temp->parent = tempParent;
			if (tempParent->left->title == kill->title) {
				tempParent->left = temp;
			}
			else if (tempParent->right->title == kill->title) {
				tempParent->right = temp;
			}
			delete(kill);
			kill = TREENULLPTR;
		}
		else {
			kill = temp;
			temp = TREENULLPTR;
			if (tempParent->left->title == kill->title) {
				tempParent->left = temp;
			}
			else if (tempParent->right->title == kill->title) {
				tempParent->right = temp;
			}
			delete(kill);
		}
	}
	else {
		return false;
	}
}

//reads an organization tree from a file, and ')' marks the end of subtrees. Return true if
//read properl or false if file is not found or improperly formatted.
//this function is theta(n log n)
bool OrgTree::read(string filename)
{
	ifstream infile;
	infile.open(filename, ios::in);
	string line, newTitle, newName;
	TREENODEPTR tempNode = TREENULLPTR;
	int count = 0;
	int forceRight = 0;
	
	if (!infile.is_open()) {
		cout << "File cannot open." << endl;
		return false;
	}
	else {
		while (getline(infile, line)) {
			if (line == ")") {
				count++;
				getline(infile, line);
				if (line != ")") {
					if (count == 1) {
						//iterate to last node in tree
						tempNode = preOrder(getRoot());

						istringstream temp(line);
						getline(temp, line, ',');
						newTitle = line;
						getline(temp, line);
						newName = line;
						newName.erase(remove(newName.begin(), newName.end(), ' '), newName.end());

						hire(tempNode, newTitle, newName);
						count = 0;
						forceRight = 1;
					}
				}
				else {
					//check to see if there is ) else add in the next name
					count++;
					getline(infile, line);
					if (line != ")") {
						if (count == 2) {
							tempNode = preOrder(getRoot());

							istringstream temp(line);
							getline(temp, line, ',');
							newTitle = line;
							getline(temp, line);
							newName = line;
							newName.erase(remove(newName.begin(), newName.end(), ' '), newName.end());
							//this is to move up 2 in the tree
							tempNode = findParent(tempNode->title, getRoot(), TREENULLPTR); //this ptr is null?
							tempNode = findParent(tempNode->title, getRoot(), TREENULLPTR);

							hire(tempNode, newTitle, newName);
							count = 0;
							forceRight = 1;
						}
					}
				}
			}
			else if (line != ")") {
				if (forceRight == 0) {
					istringstream temp(line);
					if (count == 0) {
						getline(temp, line, ',');
					}
					newTitle = line;
					getline(temp, line);
					newName = line;
					newName.erase(remove(newName.begin(), newName.end(), ' '), newName.end());

					if (getRoot() == TREENULLPTR) {
						addRoot(newTitle, newName);
					}
					else {
						hire(getRoot(), newTitle, newName);
					}
					count = 0;
				}
				else {
					istringstream temp(line);
					if (count == 0) {
						getline(temp, line, ',');
					}
					newTitle = line;
					getline(temp, line);
					newName = line;
					newName.erase(remove(newName.begin(), newName.end(), ' '), newName.end());
					tempNode = preOrder(getRoot());
					
					tempNode->left = new TreeNode(newTitle, newName);
					size++;
				}
			}
		}
	}
	return true;
}

//this function calls a recursive helper function to write the tree into a file
//this function is theta(n)
void OrgTree::write(string filename)
{
	fstream file;
	file.open(filename);
	TREENODEPTR temp = getRoot();
	writeRecursive(temp, file);
	file.close();
}

//this is the recursive helper function for the function write which writes a tree to a file
//this function is theta(n)
void OrgTree::writeRecursive(TREENODEPTR node, fstream& file)
{
	if (!node) {
		file << ")\n";
		return;
	}
	else {
		file << node->title << ", " << node->name << endl;
	}
	writeRecursive(node->left, file);
	writeRecursive(node->right, file);
}

//an extra helper function that will take you to the last node in the tree in preorder
//this function is theta(n^2 + n)
TREENODEPTR OrgTree::preOrder(TREENODEPTR node)
{
	TREENODEPTR temp = node;
	if (node == TREENULLPTR) {
		return TREENULLPTR;
	}
	for (int i = 0; i < size; i++) {
		if (node == root) {
			node = node->left;
		}
		else if (node->left != TREENULLPTR && node->right != TREENULLPTR) {
			if (node->right != TREENULLPTR) {
				node = node->right;
			}
		}
		else if (node->left == TREENULLPTR && node->right != TREENULLPTR) {
			if (node->right != TREENULLPTR) {
				node = node->right;
			}
		}
		else if (node->left != TREENULLPTR && node->right == TREENULLPTR) {
			if (node->left != TREENULLPTR) {
				node = node->left;
			}
		}
		else {
			if (node->right != TREENULLPTR) {
				node = node->right;
			}
		}
	}
	return node;
}

//finds parent of node searching for, this is a helper function
//this function is theta(log n)?
TREENODEPTR OrgTree::findParent(string titleSearch, TREENODEPTR node, TREENODEPTR parentNode)
{
	if (node == TREENULLPTR) {
		return TREENULLPTR;
	}
	if (node->title == titleSearch) {
		return parentNode;
	}
	
	TreeNode *result = findParent(titleSearch, node->left, node);
	if (result) return result;
	result = findParent(titleSearch, node->right, node);
	if (result) return result;
	return TREENULLPTR;
}


