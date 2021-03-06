#pragma once


#include <iostream>

using namespace std;

class BlackjackGame
{
public: 

	BlackjackGame(int); //Initializes the game, and takes in the size of the deck to be used in the game

private:

	void StartRound(); //Starts another round starting with bets, and then dealing the cards

	void PlayGame(); //Gameplay loop, has player take turn, and then dealer take turn.

	void PlayerTurn(); //Allows player to take turn

	void DealerTurn(); //Allows dealer to take turn

	void EndGame(); //Checks player and dealers cards and determines winner

	int CheckWin(int); //Checks win for specified deck 
};

