#include "BlackjackDealer.h"
#include "BlackjackHand.h"

#include <iostream>

using namespace std;

bool hideCard = true;
PlayingCard cardTwo;
BlackjackHand hand;

BlackjackDealer::BlackjackDealer()
{
	hideCard = true;
	hand = BlackjackHand();
}

void BlackjackDealer::DisplayCards()
{
	if (hideCard)
	{
		cout << hand.cardNames << " ?\n";
		cout << hand.handValue;
	}
	else {
		cout << hand.cardNames << "\n" << hand.handValue << "\n" << endl;
	}
}

int BlackjackDealer::GetHandValue()
{
	return hand.handValue;
}

void BlackjackDealer::AddCard(PlayingCard newCard)
{
	if (hand.numCards == 1 && hideCard)
	{
		cardTwo = newCard;
	}
	else {
		hand.AddCardName(newCard.GetCardName());
		hand.AddCardValue(newCard.GetCardNumber());
	}

}

void BlackjackDealer::TakeTurn()
{
	hideCard = false;
	AddCard(cardTwo);
}
