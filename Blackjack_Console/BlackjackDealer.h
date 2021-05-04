#pragma once

#include "PlayingCard.h"

class BlackjackDealer
{
private:

public:

	BlackjackDealer(); //Default constructor

	void DisplayCards(); //Displays cards

	int GetHandValue(); //Returns hand value

	void AddCard(PlayingCard); //Accepts card dealt

	void TakeTurn(); //Allows the dealer to take turn
	
};

