// Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include "Orgtree.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	OrgTree o1, fileTree;
	o1.addRoot("R1", "R1");
	o1.addRoot("R2", "R2");

	o1.printSubTree(o1.getRoot());
	o1.leftmostChild(o1.getRoot());
	o1.rightSibling(o1.getRoot());
	cout << "Size: " << o1.getSize() << endl;
	o1.find("R1");
	o1.find("R3");
	o1.hire(o1.getRoot(), "R3", "R3");
	o1.hire(o1.find("R1"), "R4", "R4");
	o1.hire(o1.getRoot(), "R5", "R5");
	o1.printSubTree(o1.getRoot());
	o1.printSubTree(o1.find("R3"));
	o1.leftmostChild(o1.find("R1"));
	o1.rightSibling(o1.find("R4"));

	o1.fire("R4");
	o1.printSubTree(o1.getRoot());
	fileTree.read("file.txt");
	fileTree.write("treeToFile.txt");

	system("pause");
    return 0;
}

