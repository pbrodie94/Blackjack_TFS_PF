#pragma once

#include <iostream>

using namespace std;

class CardDeck
{
public:

	CardDeck(int, int) {}; //Initializes deck taking in how many decks (from 1 to 8) and how many jokers

	string DrawCard(int); //Draws a card from the deck and returns it as a string. takes in number of cards to be drawn

	void ShuffleDeck(); //Shuffles the deck

	void Discard(); //Discards a card from the deck when finished. Puts it into a discard pile to be shuffled back in when necessary

};

