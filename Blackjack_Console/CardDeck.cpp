#include "CardDeck.h"

#include <vector>
#include <random>
#include <algorithm>

int numDecks = 1;
vector <PlayingCard>deck;

CardDeck::CardDeck(int decks)
{
	decks = decks;

	CreateDeck();
}

void CardDeck::CreateDeck()
{
	for (int i = 0; i < numDecks; i++)
	{
		int suit = 1;
		int number = 1;

		for (int j = 0; j < 52; j++)
		{

			if (number <= 13)
			{
				deck.push_back(PlayingCard(number, suit));

				number++;
			}
			else {

				number = 1;

				suit++;
			}

		}
	}

	ShuffleDeck();
}

PlayingCard CardDeck::DrawCard()
{
	PlayingCard card; 
	
	if (deck.size() < 1)
	{
		DestroyDeck();

		CreateDeck();
	}

	card = deck[deck.size() - 1];

	deck.erase(deck.end() - 1);


	return card;
}

void CardDeck::ShuffleDeck()
{
	unsigned seed = 0;
	shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

void CardDeck::DestroyDeck()
{
	deck.clear();
}
