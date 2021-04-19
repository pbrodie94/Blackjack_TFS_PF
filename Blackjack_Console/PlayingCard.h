#pragma once

#include <iostream>

using namespace std;

class PlayingCard
{
public:

	PlayingCard() {};

	PlayingCard(int, int); //Initializes the card's value

	string GetCardName(); //Returns a string of the cards suit and numeric value

private:

	int cardNumber = 1; //The number on the card from 1 (Ace) to 13 (King) + 14 (joker)
	int cardSuit = 1; //Card suit (Spades, Clubs, Hearts, Diamonds)

};

