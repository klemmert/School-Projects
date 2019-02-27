#include "pch.h"
#include "Player.h"

#include <vector>

using namespace std;


Player::Player()
{
}


Player::Player(int playerID, int scoreCount, vector<int> hand)
{
	id = playerID;
	score = scoreCount;
	playerHand = hand;
}

Player::~Player()
{
}

void Player::setPlayerScoreCount(int scoreCount)
{
	score = scoreCount;
}

int Player::getPlayerScoreCount()
{
	return score;
}

void Player::setID(int playerID)
{
	id = playerID;
}

int Player::getID()
{
	return id;
}

void Player::setPlayerHand(vector <int> hand)
{
	playerHand = hand;
}

vector<int> Player::getPlayerHand()
{
	return playerHand;
}
