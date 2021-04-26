#pragma once

#include <iostream>

using namespace std;

class PlayingCard
{
private:
	int cardNumber; //The number on the card from 1 (Ace) to 13 (King) + 14 (joker)

	int cardSuit; //Card suit (Spades, Clubs, Hearts, Diamonds)

public:

	PlayingCard();

	PlayingCard(int, int); //Initializes the card's value

	string GetCardName(); //Returns a string of the cards suit and numeric value

	int GetCardNumber(); //Returns true if the card is an ace

};

