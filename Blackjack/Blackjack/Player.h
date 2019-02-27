#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h> 
#include <ctime>
#include <stdlib.h>
#include <stdio.h> 
#pragma once

using namespace std;
class Player
{
private:
	int id;
	int score;
	vector <int> playerHand;
public:
	Player();
	Player(int playerID, int scoreCount, vector<int> hand);
	~Player();

	void setPlayerScoreCount(int scoreCount);
	int getPlayerScoreCount();
	void setID(int playerID);
	int getID();

	void setPlayerHand(vector <int> hand);
	vector<int> getPlayerHand();
};

