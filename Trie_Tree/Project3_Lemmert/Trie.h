#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

const int ALPHABET = 26;

using namespace std;

#pragma once
class trieNode 
{
public:
	trieNode *children[ALPHABET];
	bool endOfWord;
};
class Trie
{
private:
	int wordCount = 0;
	int nodeCount = 0;
	int totalCount = 0;
	trieNode *root;
	vector<string> list;
public:
	Trie();
	~Trie();

	bool insert(string word);
	int count();
	int getSize();
	bool find(string word);
	int completeCount(string word);
	vector<string> complete(string word);
	void completeRec(trieNode *current, string word);

	trieNode *getNode();
	bool lastNode(trieNode *current);
};

