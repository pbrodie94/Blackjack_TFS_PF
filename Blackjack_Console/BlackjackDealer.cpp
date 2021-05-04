#include "BlackjackDealer.h"
#include "BlackjackHand.h"

#include <iostream>

using namespace std;

bool hideCard = true; //Says when to hide second card from view of player
PlayingCard cardTwo; //Stores the second card while it is being hidden
BlackjackHand hand; //Hand class that stores the cards in the dealers hand

BlackjackDealer::BlackjackDealer()
{
	hideCard = true; //Hide the dealer's second card by default
	hand = BlackjackHand(); //Resets the dealers hand
}

void BlackjackDealer::DisplayCards()
{
	//If the card is to be hidden, show the first card in the hand, and then 
	if (hideCard)
	{
		cout << hand.cardNames << " ?\n";
		cout << "Total: " << hand.handValue;
	}
	else {
		cout << hand.cardNames << "\nTotal: " << hand.handValue << "\n" << endl;
	}
}

int BlackjackDealer::GetHandValue()
{
	//Returns the value of the dealer's hand
	return hand.handValue;
}

void BlackjackDealer::AddCard(PlayingCard newCard)
{
	//If the first card has been recieved, and the dealers second card is still to be hidden
	if (hand.numCards == 1 && hideCard)
	{
		//Temporaritly store it in the placeholder object
		cardTwo = newCard;
	}
	else {
		//Otherwise add the card to the hand normally
		hand.AddCardName(newCard.GetCardName());
		hand.AddCardValue(newCard.GetCardNumber());
	}
}

void BlackjackDealer::TakeTurn()
{
	//When it's the dealers turn, unhide the card, and add it to the dealer's hand
	hideCard = false;
	AddCard(cardTwo);
}
