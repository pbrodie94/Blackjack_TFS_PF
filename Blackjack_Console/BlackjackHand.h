#pragma once

#include <iostream>

class BlackjackHand
{
private:

public:

	BlackjackHand(); //Initializes hand

	void AddCardName(std::string); //Adds the name of the card

	void AddCardValue(int); //Adds the value of the card

	std::string cardNames;
	int handValue;
	int numCards;
	int numAces;
	bool stand;
	bool blackJack;
	bool bust;

};

