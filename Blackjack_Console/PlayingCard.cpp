#include "PlayingCard.h"

#include <string>

//Sets the card to Ace of Spades by default
PlayingCard::PlayingCard() {
	PlayingCard::cardNumber = 1;
	PlayingCard::cardSuit = 1;
}

//Sets the card at creation
PlayingCard::PlayingCard(int c, int s) {
	PlayingCard::cardNumber = c;
	PlayingCard::cardSuit = s;
}

//Returns the card name based on the card's suit and number
string PlayingCard::GetCardName()
{
	string name;

	//Sets the value of the card
	switch (PlayingCard::cardNumber)
	{
	case 1:

		name = "Ace of ";

		break;

	case 11:

		name = "Jack of ";

		break;

	case 12:

		name = "Queen of ";

		break;

	case 13:

		name = "King of ";

		break;

	default:

		name = to_string(PlayingCard::cardNumber) + " of "; 

		break;
	}

	//Gives the playing card a suit
	switch (PlayingCard::cardSuit)
	{
	case 1:

		name += "Spades";

		break;

	case 2:

		name += "Diamonds";

		break;

	case 3:

		name += "Clubs";

		break;

	case 4:

		name += "Hearts";

		break;
	}

	return name;
}

//Returns the card's number
int PlayingCard::GetCardNumber()
{
	return PlayingCard::cardNumber;
}