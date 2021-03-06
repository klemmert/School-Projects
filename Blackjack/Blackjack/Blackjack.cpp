/*
Katherine Lemmert
We are playing with 1 deck.
Player will play until they hit 17, same as dealer.
Ace is values as 1.
If Ace is drawn and makes value over 21, make value 1 no matter what game.

Dealer Rules:
Dealer will continue to Hit until the house hand has at-least 17 points.

What ifs:
What if the player stops hits at 18? Will that give the player a better advantage over the dealer, who stops at 18?
What are the odds of the player winning if it followed the Single-Deck Blackjack strategy where the dealer does not stand on soft 17?

*/

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h> 
#include <ctime>
#include <stdlib.h>
#include <stdio.h> 

#include "Player.cpp"

using namespace std;

//global variables
vector<int> cardDeck;
int stopAt18 = 0;
int strategy = 0;
int cheater = 0;

//functions
void createDeck() {
	int cardCount = 0;
	int type = 1; //type of cards, start with ace
	while (cardCount < 52) {
		for (int i = 0; i < 4; i++) {
			cardDeck.push_back(type);
			cardCount++;
		}
		type++;
	}
}

void shuffle() {
	int cardIndexFromDeck = 0;
	vector<int> tempDeck;
	int deckSize = cardDeck.size();

	for (int i = 0; i < deckSize; i++) {
		cardIndexFromDeck = (rand() % cardDeck.size()); //select random card
		tempDeck.push_back(cardDeck[cardIndexFromDeck]); //put in temporary new deck, this is the shuffled deck
		cardDeck.erase(cardDeck.begin() + (cardIndexFromDeck)); //remove card from main deck so it isn't reused
	}

	//copy temp deck's contents into main deck. Deck is now shuffled!
	for (int i = 0; i < tempDeck.size(); i++) {
		cardDeck.push_back(tempDeck[i]);
	}
}

//helper functions for round
int draw() {
	int card = 0;
	try {
		card = cardDeck.at(0); //this draws the card from the top of the deck
		cardDeck.erase(cardDeck.begin()); //remove card from the card deck
	}
	catch (exception e) {
		cout << "There is nothing in the deck.";
	}
	return card;
}

int valueOfCard(int card) {
	if (strategy == 1) { //if we are running simulation of ace being worth 11 points
		if (card == 1) { //if ace, return value of 11
			return 11;
		}
	}
	else {
		if (card == 1) { //ace is 1
			return 1;
		}
	}

	if (card == 2) { //2
		return 2;
	}
	else if (card == 3) { //3
		return 3;
	}
	else if (card == 4) { //4
		return 4;
	}
	else if (card == 5) { //5
		return 5;
	}
	else if (card == 6) { //6
		return 6;
	}
	else if (card == 7) { //7
		return 7;
	}
	else if (card == 8) { //8
		return 8;
	}
	else if (card == 9) { //9
		return 9;
	}
	else if (card == 10 || card == 11 || card == 12 || card == 13) { //10, Jack, Queen, King
		return 10;
	}
}

/*
This function is a function that checks the players score. If the score is over 21, return -1 meaning the player has lost.
If the score is 21 or under, return 1 meaning that the score is within game bounds.
*/
int checkScoreBound(Player player) {
	int value = player.getPlayerScoreCount();

	if (value <= 21) {
		return 1;
	}
	else {
		return -1;
	}
}

/*
This function will compare both players score. Since it has already been approved that both players have values within
bounds, check to see who has the highest number. The highest number is the winner. If there is a tie, return -1 and no
player wins.
*/
int compareScore(Player player, Player dealer) {
	int playerScore = player.getPlayerScoreCount();
	int dealerScore = dealer.getPlayerScoreCount();

	if (playerScore > dealerScore) {
		return 1;
	}
	else if (playerScore < dealerScore) {
		return 2;
	}
	else if (playerScore == dealerScore) {
		return -1;
	}
}

Player hit(int score, Player player) {
	int card = 0;
	int value = 0;
	vector<int> hand = player.getPlayerHand();

	card = draw();
	hand.push_back(card);
	value = valueOfCard(card);
	score = score + value;

	//if there is an ace and the score ends up being over 21 due to the ace, even if ace is valued at 11, value it as 1
	if (strategy == 1 && score > 21) {
		for (int i = 0; i < hand.size(); i++) {
			if (hand[i] == 1) {
				score = score - 10; //ace turns to 1, altering score
				break;
			}
		}
	}

	player.setPlayerScoreCount(score);
	player.setPlayerHand(hand); //update player's hand

	return player;
}

Player startRound(Player player) {
	int card = 0;
	int score = 0; //keeps track of player score
	vector<int> hand = player.getPlayerHand();

	//draw first two cards to start round
	card = draw();
	hand.push_back(card);
	score = valueOfCard(card);
	card = draw();
	hand.push_back(card);
	score = score + valueOfCard(card);

	//update player's hand
	player.setPlayerHand(hand);

	if (stopAt18 == 1) { //if player 1 is supposed to stop at 18
		if (player.getID() == 1) {
			while (score < 18) { //play until user or dealer has score of 18 or higher
				player = hit(score, player);
				score = player.getPlayerScoreCount();
			}
		}
		else { //this is for the dealer
			while (score < 17) { //play until user or dealer has score of 17 or higher
				player = hit(score, player);
				score = player.getPlayerScoreCount();
			}
		}
	}
	else {
		while (score < 17) { //play until user or dealer has score of 17 or higher
			player = hit(score, player);
			score = player.getPlayerScoreCount();
		}
	}

	//update players score
	player.setPlayerScoreCount(score);
	return player;
}

float compareWinnings(int dWins, int games) {
	float percentWinning = ((float)dWins / (float)games);
	percentWinning = percentWinning * 100;

	return percentWinning;
}

/*
This function implements how the users would play if they played with a pre-determined strategy
*/
int strategyPlay(Player player, Player dealer) {
	vector<int> pHand = player.getPlayerHand();
	vector<int> dHand = dealer.getPlayerHand();
	int pCard = 0;
	int dCard = 0;
	int pScore = 0; //keeps track of player score
	int dScore = 0; //keeps track of dealer score
	int stand = 0;
	int withinBounds = 0;
	int winner = 0;

	//draw first two cards to start round for the player
	pCard = draw();
	pHand.push_back(pCard);
	pScore = valueOfCard(pCard);
	pCard = draw();
	pHand.push_back(pCard);
	pScore = pScore + valueOfCard(pCard);

	player.setPlayerHand(pHand); //update player hand

	//for the dealer, draw card, player knows what first card is
	dCard = draw();
	dHand.push_back(dCard);
	dScore = valueOfCard(dCard);
	dCard = draw();
	dHand.push_back(dCard);
	dScore = dScore + valueOfCard(dCard);

	dealer.setPlayerHand(dHand); //update dealer hand

	//player's turn
	while (stand == 0) {
		//if player score is 11 below, always hit the next turn
		if (pScore <= 11) {
			//hit
			player = hit(pScore, player);
			pScore = player.getPlayerScoreCount();
		}

		if (pScore == 12 && (dScore != 4 || dScore != 5 || dScore != 6)) {
			//hit
			player = hit(pScore, player);
			pScore = player.getPlayerScoreCount();
		}
		else if (pScore == 12 && (dScore == 4 || dScore == 5 || dScore == 6)) {
			stand = 1;
		}

		if ((pScore == 13 || pScore == 14 || pScore == 15 || pScore == 16) && (dScore != 2 || dScore != 3 || dScore != 4 || dScore != 5 || dScore != 6)) {
			//hit
			player = hit(pScore, player);
			pScore = player.getPlayerScoreCount();
		}
		else if ((pScore == 13 || pScore == 14 || pScore == 15 || pScore == 16) && (dScore == 2 || dScore == 3 || dScore == 4 || dScore == 5 || dScore == 6)) {
			stand = 1;
		}

		if (pScore >= 17) {
			stand = 1;
		}
	}

	withinBounds = checkScoreBound(player);
	if (withinBounds) {
		//dealer's turn
		while (dScore < 17) { //play until user or dealer has score of 17 or higher
			dealer = hit(dScore, dealer);
			dScore = dealer.getPlayerScoreCount();
		}
	}
	else { //else dealer is the winner
		return 2;
	}

	withinBounds = checkScoreBound(dealer);

	if (withinBounds) { //if dealer score is within bounds, compare scores to find winner
		winner = compareScore(player, dealer);
		return winner;
	}
	else { //dealer busted, player is the winner
		return 1;
	}
}

/*
This function sets up the game
*/
void setUp() {
	createDeck();
	shuffle();
}

void breakDown() {
	cardDeck.clear();
}

int playGame() {
	vector<int>tempHand;
	Player player1(1, 0, tempHand); //player
	Player player2(2, 0, tempHand); //dealer
	int winner = 0;
	int withinBounds = 0;

	setUp(); //setup the deck needed for the game

	if (strategy == 1) {
		winner = strategyPlay(player1, player2);
		breakDown();
		return winner;
	}
	else {
		player1 = startRound(player1); //update player score
		withinBounds = checkScoreBound(player1);

		if (withinBounds) { //if player 1 is within bounds, play for dealer
			player2 = startRound(player2); //update player score for dealer
		}
		else { //else dealer is the winner
			breakDown();
			return 2;
		}

		withinBounds = checkScoreBound(player2);

		if (withinBounds) { //if dealer score is within bounds, compare scores to find winner
			if (cheater == 1) {
				if (player2.getPlayerScoreCount() <= 19) { //if their score is less than or = 19, cheat by adding a 2 card as their hit
					vector<int> temp = player2.getPlayerHand();
					temp.push_back(2); //insert a two
					int score = player2.getPlayerScoreCount(); //get new score
					score = score + 2;

					player2.setPlayerHand(temp); //update cards dealer has
					player2.setPlayerScoreCount(score); //update score
				}
			}
			winner = compareScore(player1, player2);
			breakDown();
			return winner;
		}
		else { //dealer busted, player is the winner
			breakDown();
			return 1;
		}
	}
}

void writeFile(int playerWins, int dealerWins, int ties, int gameCount)
{
	ofstream myfile;
	if (stopAt18 == 1) {
		myfile.open("simulation.txt", ios_base::app);
		myfile << "Game1\t" << playerWins << "\t" << dealerWins << "\t" << ties << "\n";
		myfile.close();
	}
	else if (strategy == 1) {
		myfile.open("simulation.txt", ios_base::app);
		myfile << "Game2\t" << playerWins << "\t" << dealerWins << "\t" << ties << "\n";
		myfile.close();
	}
	else if (stopAt18 == 0 && strategy == 0) {
		myfile.open("simulation.txt", ios_base::app);
		myfile << "Game0\t" << playerWins << "\t" << dealerWins << "\t" << ties << "\n";
		myfile.close();
	}
}

int main()
{
	srand(time(0));
	int games = 0;
	int pWins = 0;
	int dWins = 0;
	int gameTies = 0;
	
	cout << "Playing Normal game..." << endl;
	//play 10000 games each: normal, ace as 11, stop hits at 18, and strategy

	//normal
	while (games < 100000) {
		int winner = playGame();
		if (winner == 1) {
			pWins++;
		}
		else if (winner == 2) {
			dWins++;
		}
		else if (winner == -1) {
			gameTies++;
		}
		games++;
	}
	cout << "Writing File..." << endl;
	writeFile(pWins, dWins, gameTies, games);

	//for 18
	stopAt18 = 1;
	games = 0;
	pWins = 0;
	dWins = 0;
	gameTies = 0;
	cout << "Playing 18 game..." << endl;
	while (games < 100000) {
		int winner = playGame();
		if (winner == 1) {
			pWins++;
		}
		else if (winner == 2) {
			dWins++;
		}
		else if (winner == -1) {
			gameTies++;
		}
		games++;
	}
	cout << "Writing File..." << endl;
	writeFile(pWins, dWins, gameTies, games);

	//for strategy
	stopAt18 = 0;
	strategy = 1;
	games = 0;
	pWins = 0;
	dWins = 0;
	gameTies = 0;
	cout << "Playing Strategy game..." << endl;
	while (games < 100000) {
		int winner = playGame();
		if (winner == 1) {
			pWins++;
		}
		else if (winner == 2) {
			dWins++;
		}
		else if (winner == -1) {
			gameTies++;
		}
		games++;
	}
	cout << "Writing File..." << endl;
	writeFile(pWins, dWins, gameTies, games);

	//for cheating
	strategy = 0;
	games = 0;
	pWins = 0;
	dWins = 0;
	gameTies = 0;
	cout << "Playing Cheating game..." << endl;
	while (games < 100000) {
		int cheat = 0;

		//start first 10 games not cheating
		while (games < 10) {
			int winner = playGame();
			if (winner == 1) {
				pWins++;
			}
			else if (winner == 2) {
				dWins++;
			}
			else if (winner == -1) {
				gameTies++;
			}
			games++;
		}

		float percent = compareWinnings(dWins, games);

		//if dealer is only winning less than 40%, cheat
		if (percent < 40) {
			int whenToCheat = (rand() % 10);
			int howLongToCheat = (rand() % 10);
			cheat = whenToCheat;

			for (int i = 0; i <= whenToCheat; i++) {
				if (i == cheat) {
					for (int j = 0; j <= howLongToCheat; j++) {
						//method for cheating
						cheater = 1;
						int winner = playGame();
						if (winner == 1) {
							pWins++;
						}
						else if (winner == 2) {
							dWins++;
						}
						else if (winner == -1) {
							gameTies++;
						}
						games++;
					}
					cheater = 0;
				}
				else {
					int winner = playGame();
					if (winner == 1) {
						pWins++;
					}
					else if (winner == 2) {
						dWins++;
					}
					else if (winner == -1) {
						gameTies++;
					}
					games++;
				}
			}
		}

		int winner = playGame();
		if (winner == 1) {
			pWins++;
		}
		else if (winner == 2) {
			dWins++;
		}
		else if (winner == -1) {
			gameTies++;
		}
		games++;
	}

	cout << "end";
}
