#include "stdafx.h"
#include "Trie.h"


Trie::Trie()
{
	root = NULL;
}


Trie::~Trie()
{
	for (int i = 0; i < ALPHABET; i++) {
		delete root->children[i];
	}
}

//this function inserts a new word into the trie, and duplicates are not allowed.
//It will return true if successful, and return false if not inserted
//this function is theta(n^2 + n) for runtime
//this function is theta(WN) or theta(W26) for space complexity (W for words, N for char)
bool Trie::insert(string word)
{
	//return false if duplicate word
	if (find(word) == true) {
		return false;
	}
	else {
		//start from root
		trieNode *current = root;
		//if no root, create one
		if (!current) {
			root = getNode();
			current = root;
		}
		//iterate through word characters
		for (int i = 0; i < word.length(); i++) {
			//find start position of the first letter
			int start = word[i] - 'a';
			//if letter isn't in trie, add it in
			if (!current->children[start]) {
				current->children[start] = getNode();
				nodeCount++;
			}
			//iterate to next child
			current = current->children[start];
		}
		current->endOfWord = true;
		wordCount++;
		return true;
	}
}

//this returns the number of words in the trie
//this function is theta(1) for runtime
//this functio is theta(1) for space
int Trie::count()
{
	return wordCount;
}

//this returns the number of nodes in the trie
//this function is theta(1) for runtime
//this function is theta(1) for space
int Trie::getSize()
{
	return nodeCount;
}

//this function is given a word and searches the trie. Returns true if word is found, else false
//this function is theta(n^2) for runtime
//this function is theta(WN) or theta(W26) for space complexity (W for words, N for char)
bool Trie::find(string word)
{
	trieNode *current = root;
	if (!root) {
		return false;
	}
	for (int i = 0; i < word.length(); i++) {
		int start = word[i] - 'a';
		if (!current->children[start]) { //throws a nullptr
			return false;
		}
		current = current->children[start];
	}
	return (current != NULL && current->endOfWord);
}

//this returns the number of words in the dictionary that matches the given input string
//if there are no matches, return zero
//this function is theta(1) for runtime
//this function is theta(1) for space
int Trie::completeCount(string word)
{
	//makes a temp variable, resets the count to 0 for the next word
	int tempTotal = totalCount;
	totalCount = 0;
	return tempTotal;
}

//this returns a c++ vector of strings that contail all the words in the dictionary
//that begins with the given input string. For each word, there will be one value in the vector
//and if none are found, an empty vector will return. This function also calls to a recursive helper functions
//this function is theta(n^2) for runtime
//this function is theta(WN) or theta(W26) for space complexity(W for words, N for char)
vector<string> Trie::complete(string word)
{
	vector<string> tempList;
	trieNode *current = root;
	int level;
	int n = word.length();
	//check if prefix is present
	for (level = 0; level < n; level++) {
		int start = word[level] - 'a';
		//not in trie
		if (!current->children[start]) {
			return list;
		}
		current = current->children[start];
	}

	bool aWord = ((current->endOfWord));
	bool lastWord = lastNode(current);

	if (aWord && lastWord) {
		list.push_back(word);
		totalCount++;
		//save in a temp list and clear the main list for new words to be added
		tempList = list;
		list.clear();
		return tempList;
	}
	if (!lastWord) {
		completeRec(current, word);
		tempList = list;
		list.clear();
		return tempList;
	}
}

//this is the recursive helper function for the complete function there it will go through the vector
//to search for the prefix of the word and then add the words in that part of the trie into a string vector
//this function is theta(log n^2) for runtime
//this function is theta(WN) or theta(W26) for space complexity (W for words, N for char)
void Trie::completeRec(trieNode * current, string word)
{
	//push into the vector
	if (current->endOfWord) {
		list.push_back(word);
		totalCount++;
	}

	//if all children nodes are NULL, return
	if (lastNode(current)) {
		return;
	}

	//iterate through trie
	for (int i = 0; i < ALPHABET; i++) {
		if (current->children[i]) {
			word.push_back(97 + i);
			completeRec(current->children[i], word); //done with recursion, goes back, destroys the r node and now can't read it
			word.pop_back();
		}
	}
}

//initializes the root of the tree
//this function is theta(n^2) for runtime
//this function is theta(WN) or theta(W26) for space complexity (W for words, N for char)
trieNode * Trie::getNode()
{
	trieNode *pNode = new trieNode;
	pNode->endOfWord = false;

	for (int i = 0; i < ALPHABET; i++) {
		pNode->children[i] = NULL;
	}
	return pNode;
}

//returns false if current node has a child, else if all children are null, return true
//this function is theta(n^2) for runtime
//this function is theta(WN) or theta(W26) for space complexity (W for words, N for char)
bool Trie::lastNode(trieNode * current)
{
	for (int i = 0; i < ALPHABET; i++) {
		if (current->children[i]) {
			return false;
		}
	}
	return true;
}
