#include "BlackjackHand.h"

using namespace std;

	BlackjackHand::BlackjackHand()
	{
		BlackjackHand::cardNames = "";
		BlackjackHand::handValue = 0;
		BlackjackHand::numCards = 0;
		BlackjackHand::numAces = 0;
		BlackjackHand::stand = false;
		BlackjackHand::blackJack = false;
		BlackjackHand::bust = false;
	}

	void BlackjackHand::AddCardName(string name)
	{
		BlackjackHand::cardNames += name;
		BlackjackHand::cardNames += " |";
	}

	void BlackjackHand::AddCardValue(int cardNumber)
	{
		switch (cardNumber)
		{
		case 1:

			BlackjackHand::numAces++;

			if (BlackjackHand::numCards > 2)
			{
				if (BlackjackHand::handValue + 11 > 21)
				{
					BlackjackHand::handValue += 1;
				}
				else {

					BlackjackHand::handValue += 11;
				}
			}
			else {
				BlackjackHand::handValue += 11;
			}

			break;

		case 11:

		case 12:

		case 13:

			BlackjackHand::handValue += 10;

			break;

		default:

			BlackjackHand::handValue += cardNumber;

			break;
		}

		BlackjackHand::numCards++;

		if (BlackjackHand::numCards == 2 && BlackjackHand::handValue == 21)
		{
			BlackjackHand::blackJack = true;
			BlackjackHand::stand = true;
		}
		else if (BlackjackHand::handValue > 21)
		{
			BlackjackHand::bust = true;
		}
	}