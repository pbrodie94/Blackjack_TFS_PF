#pragma once

#include "BlackjackDealer.h"
#include "BlackjackDealer.h"
#include "PlayingCard.h"

#include <iostream>

using namespace std;

class BlackjackPlayer
{
public:

	BlackjackPlayer() {};

	BlackjackPlayer(int, BlackjackDealer*); //Initializes player and gives them their starting chips

	int PlaceBet() { return 0; }; //Returns playuer's bet

	void TakeTurn(); //Allows player to take their turn

};

