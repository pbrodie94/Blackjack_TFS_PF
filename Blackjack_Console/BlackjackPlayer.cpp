#include "BlackjackPlayer.h"
#include "BlackjackHand.h"

#include <iostream>

using namespace std; 

BlackjackHand handOne; 
BlackjackHand handTwo;

BlackjackPlayer::BlackjackPlayer()
{
	BlackjackPlayer::chips = 1000;
	BlackjackPlayer::split = false;
}

BlackjackPlayer::BlackjackPlayer(int startingChips)
{
	BlackjackPlayer::chips = startingChips;
	BlackjackPlayer::split = false;
}

int BlackjackPlayer::PlaceBet()
{
	int bet;
	bool invalidBet = false;

	do {
		cout << "Your Chips: $" << BlackjackPlayer::chips << "\n";
		cout << "How much would you like to bet? ";
		cin >> bet;

		if (bet > 0 && bet < BlackjackPlayer::chips)
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

	cout << "\nRemaining chips: " << BlackjackPlayer::chips << "\n" << endl;

	return bet;
}

void BlackjackPlayer::AddCards(PlayingCard newCard)
{
	if (!handOne.stand)
	{
		handOne.AddCardName(newCard.GetCardName());

		handOne.AddCardValue(newCard.GetCardNumber());
	}
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

void BlackjackPlayer::WinHand(int winnings)
{
	cout << "You won $" << winnings << "!";

	BlackjackPlayer::chips += winnings;
}

void BlackjackPlayer::ResetHand()
{
	handOne = BlackjackHand();
	handTwo = BlackjackHand();
	BlackjackPlayer::split = false;
}