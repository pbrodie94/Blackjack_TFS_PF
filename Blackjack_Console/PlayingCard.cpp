#include "PlayingCard.h"

#include <string>

PlayingCard::PlayingCard() {
	PlayingCard::cardNumber = 1;
	PlayingCard::cardSuit = 1;
}

PlayingCard::PlayingCard(int c, int s) {
	PlayingCard::cardNumber = c;
	PlayingCard::cardSuit = s;
}

string PlayingCard::GetCardName()
{
	string name;

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

int PlayingCard::GetCardNumber()
{
	return PlayingCard::cardNumber;
}