#pragma once

#include "BlackjackDealer.h"
#include "BlackjackPlayer.h"

#include <iostream>

using namespace std;

class BlackjackGame
{
public: 

	BlackjackGame(int); //Initializes the game, and takes in the size of the deck to be used in the game

private:

	void StartRound() {}; //Starts another round starting with bets, and then dealing the cards

	void PlayGame(); //Gameplay loop, has player take turn, and then dealer take turn.
};

