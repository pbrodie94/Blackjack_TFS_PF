#pragma once

#include <iostream>
#include "PlayingCard.h"

using namespace std;

class CardDeck
{
private:

	void CreateDeck(); //Creates the deck

	void ShuffleDeck(); //Shuffles the deck

public:

	CardDeck() {};

	CardDeck(int); //Initializes deck taking in how many decks (from 1 to 8)

	PlayingCard DrawCard(); //Draws a card from the deck and returns it

	void DestroyDeck(); //Destroys the card deck 

};

