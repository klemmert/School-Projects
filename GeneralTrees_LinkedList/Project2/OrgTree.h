#include "stdafx.h"
#include <string>
#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL

using namespace std;

#pragma once
class TreeNode
{
public:
	string title;
	string name;
	TreeNode * parent = TREENULLPTR;
	TreeNode * left = TREENULLPTR;
	TreeNode * right = TREENULLPTR;

	TreeNode() {
		title = "";
		name = "";
	}

	TreeNode(string newTitle, string newName) {
		title = newTitle;
		name = newName;
	}
};

class OrgTree
{
private:
	TreeNode * root;
	int size = 0;
public:
	OrgTree();
	~OrgTree();
	void destroy(TREENODEPTR node);
	void addRoot(string title, string name);
	unsigned int getSize();
	TREENODEPTR getRoot();
	TREENODEPTR leftmostChild(TREENODEPTR node);
	TREENODEPTR rightSibling(TREENODEPTR node);
	void printSubTree(TREENODEPTR subTreeRoot);
	TREENODEPTR find(string titleSearch);
	TREENODEPTR findHelper(string titleSearch, TREENODEPTR node);
	void hire(TREENODEPTR node, string newTitle, string newName);
	bool fire(string formerTitle);
	bool read(string filename);
	void write(string filename);
	void writeRecursive(TREENODEPTR node, fstream& file);
	TREENODEPTR preOrder(TREENODEPTR node);
	TREENODEPTR findParent(string titleSearch, TREENODEPTR node, TREENODEPTR parentNode);
};

