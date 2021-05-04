#include "BlackjackPlayer.h"
#include "BlackjackHand.h"

#include <iostream>

using namespace std; 

BlackjackHand handOne; //Player's default hand
BlackjackHand handTwo; //Used if the player is able to split

//Holds onto the first and second card of a hand in case of split
PlayingCard firstCard; 
PlayingCard secondCard;
int numCards; //Number of cards in a hand

BlackjackPlayer::BlackjackPlayer()
{
	//Sets the player's default chip amount
	BlackjackPlayer::chips = 1000;
	BlackjackPlayer::split = false;
	BlackjackPlayer::canSplit = false;
	numCards = 0;
}

BlackjackPlayer::BlackjackPlayer(int startingChips)
{
	//Allows a custom amount of starting chips. Has not yet been implemented
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

		//Checks for garbage input
		if (!cin.fail() && bet > 0 && bet <= BlackjackPlayer::chips)
		{
			invalidBet = false;
		}
		else {
			
			cout << "\n\n Invalid bet, please reenter. \n" << endl;
			invalidBet = true;
			cin.clear();
			cin.ignore(256, '\n');
		}

		cout << endl;

	} while (invalidBet);

	//Subtract player's bet from chips
	BlackjackPlayer::chips -= bet;

	//Displays player's remaining chips
	cout << "\nRemaining chips: $" << BlackjackPlayer::chips << "\n" << endl;

	//Returns the bet to the game class
	return bet;
}

void BlackjackPlayer::AddCards(PlayingCard newCard)
{
	numCards++;

	//If this is the first card recieved, also add it to the first card place holder for checking values for splitting
	if (numCards == 1)
	{
		firstCard = newCard;
	}
	else if (numCards == 2)
	{
		//If second card, add to second place holder
		secondCard = newCard;

		//If the first two card's values are the same, the player may split
		if (firstCard.GetCardNumber() == secondCard.GetCardNumber())
		{
			BlackjackPlayer::canSplit = true;
		}
	}
	else if (numCards == 3)
	{
		//Once the player has recieved more than two cards, they can no longer split
		BlackjackPlayer::canSplit = false;
	}

	//If the first hand has not stood, add it to the first hand
	if (!handOne.stand)
	{
		handOne.AddCardName(newCard.GetCardName());

		handOne.AddCardValue(newCard.GetCardNumber());
	}
	else {
		//Otherwise add it to the second hand
		handTwo.AddCardName(newCard.GetCardName());

		handTwo.AddCardValue(newCard.GetCardNumber());
	}
}

void BlackjackPlayer::Stand()
{
	//Stand hands based on whether or not they've already stood
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
	//Sets the split to true
	BlackjackPlayer::split = true;

	//Reset both hands
	handOne = BlackjackHand();
	handTwo = BlackjackHand();

	//Add both the cards to the first hand
	handOne.AddCardName(firstCard.GetCardName());
	handOne.AddCardValue(firstCard.GetCardNumber());
	handOne.AddCardName(cardOne.GetCardName());
	handOne.AddCardValue(cardOne.GetCardNumber());

	//Add both cards to the second hand
	handTwo.AddCardName(secondCard.GetCardName());
	handTwo.AddCardValue(secondCard.GetCardNumber());
	handTwo.AddCardName(cardTwo.GetCardName());
	handTwo.AddCardValue(cardTwo.GetCardNumber());

}

void BlackjackPlayer::DisplayHand()
{
	//Displays the names of all the cards in a hand
	cout << handOne.cardNames << "\n";
	cout << "Total: " << handOne.handValue << "\n";

	//If the player has split, also show the second hand
	if (BlackjackPlayer::split)
	{
		cout << "\n" << handTwo.cardNames << "\n";
		cout << "Total: " << handTwo.handValue << "\n";
	}

	cout << endl;
}

int BlackjackPlayer::GetHandValue(int hand)
{
	//Returns the value of the specified hand
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
	//Adds chips back to the player's chip stash
	BlackjackPlayer::chips += c;
}

void BlackjackPlayer::ResetHand()
{
	//Resets all values to get ready for a new round and hand
	handOne = BlackjackHand();
	handTwo = BlackjackHand();
	BlackjackPlayer::split = false;
	BlackjackPlayer::canSplit = false;
	numCards = 0;
}

bool BlackjackPlayer::IsBlackjack()
{
	//Returns back if player's hand is a blackjack
	return handOne.blackJack;
}

//Allows the game class to take chips without prompting player
void BlackjackPlayer::TakeChips(int amount)
{
	chips -= amount;

	//Once the chips have been taken, display the remaining amount
	cout << "\nChips Remaining: $" << BlackjackPlayer::chips << endl;
}