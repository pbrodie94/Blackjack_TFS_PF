#include "BlackjackPlayer.h"
#include "BlackjackHand.h"

#include <iostream>

using namespace std; 

BlackjackHand handOne; 
BlackjackHand handTwo;

PlayingCard firstCard;
PlayingCard secondCard;
int numCards;

BlackjackPlayer::BlackjackPlayer()
{
	BlackjackPlayer::chips = 1000;
	BlackjackPlayer::split = false;
	BlackjackPlayer::canSplit = false;
	numCards = 0;
}

BlackjackPlayer::BlackjackPlayer(int startingChips)
{
	BlackjackPlayer::chips = startingChips;
	BlackjackPlayer::split = false;
	BlackjackPlayer::canSplit = false;
	numCards = 0;
}

int BlackjackPlayer::PlaceBet()
{
	int bet;
	bool invalidBet = false;

	do {
		cout << "Your Chips: $" << BlackjackPlayer::chips << "\n";
		cout << "How much would you like to bet? ";
		cin >> bet;

		if (bet > 0 && bet <= BlackjackPlayer::chips)
		{
			invalidBet = false;
		}
		else {
			
			cout << "\n\n Invalid bet, please reenter. \n" << endl;
			invalidBet = true;
		}

		cout << endl;

	} while (invalidBet);

	BlackjackPlayer::chips -= bet;

	cout << "\nRemaining chips: $" << BlackjackPlayer::chips << "\n" << endl;

	return bet;
}

void BlackjackPlayer::AddCards(PlayingCard newCard)
{
	numCards++;

	if (numCards == 1)
	{
		firstCard = newCard;
	}
	else if (numCards == 2)
	{
		secondCard = newCard;

		if (firstCard.GetCardNumber() == secondCard.GetCardNumber())
		{
			BlackjackPlayer::canSplit = true;
		}
	}
	else if (numCards == 3)
	{
		BlackjackPlayer::canSplit = false;
	}

	if (!handOne.stand)
	{
		handOne.AddCardName(newCard.GetCardName());

		handOne.AddCardValue(newCard.GetCardNumber());
	}
	else {
		handTwo.AddCardName(newCard.GetCardName());

		handTwo.AddCardValue(newCard.GetCardNumber());
	}
}

void BlackjackPlayer::Stand()
{
	if (!handOne.stand)
	{
		handOne.stand = true;
	}
	else {
		handTwo.stand = true;
	}
}

void BlackjackPlayer::Split(PlayingCard cardOne, PlayingCard cardTwo)
{
	BlackjackPlayer::split = true;

	handOne = BlackjackHand();
	handTwo = BlackjackHand();

	handOne.AddCardName(firstCard.GetCardName());
	handOne.AddCardValue(firstCard.GetCardNumber());
	handOne.AddCardName(cardOne.GetCardName());
	handOne.AddCardValue(cardOne.GetCardNumber());

	handTwo.AddCardName(secondCard.GetCardName());
	handTwo.AddCardValue(secondCard.GetCardNumber());
	handTwo.AddCardName(cardTwo.GetCardName());
	handTwo.AddCardValue(cardTwo.GetCardNumber());

}

void BlackjackPlayer::DisplayHand()
{
	cout << handOne.cardNames << "\n";
	cout << "Total: " << handOne.handValue << "\n";

	if (BlackjackPlayer::split)
	{
		cout << handTwo.cardNames << "\n";
		cout << "Total: " << handTwo.handValue << "\n";
	}

	cout << endl;
}

int BlackjackPlayer::GetHandValue(int hand)
{
	if (hand == 1)
	{
		return handOne.handValue;
	}
	else if (hand == 2)
	{
		return handTwo.handValue;
	}
}

void BlackjackPlayer::AddChips(int c)
{
	BlackjackPlayer::chips += c;
}

void BlackjackPlayer::ResetHand()
{
	handOne = BlackjackHand();
	handTwo = BlackjackHand();
	BlackjackPlayer::split = false;
	BlackjackPlayer::canSplit = false;
	numCards = 0;
}

bool BlackjackPlayer::IsBlackjack()
{
	return handOne.blackJack;
}

void BlackjackPlayer::TakeChips(int amount)
{
	chips -= amount;

	cout << "\nChips Remaining: $" << BlackjackPlayer::chips << endl;
}