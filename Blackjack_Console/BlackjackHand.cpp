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
		//Adds the card's names to the string of card names
		BlackjackHand::cardNames += name;
		BlackjackHand::cardNames += " |";
	}

	void BlackjackHand::AddCardValue(int cardNumber)
	{
		//Takes in the card's value and assignes the appropriate value to the overall hand value
		switch (cardNumber)
		{
		case 1:
			//If the card is an ace, increase the number of aces to be checked in case the value needs to be switched to 1
			BlackjackHand::numAces++;

			//Add the default value of 11
			BlackjackHand::handValue += 11;

			break;

		case 11:

		case 12:

		case 13:

			//All face cards add 10
			BlackjackHand::handValue += 10;

			break;

		default:

			//Any other card adds its number value
			BlackjackHand::handValue += cardNumber;

			break;
		}

		//Increase card count
		BlackjackHand::numCards++;

		//If the card count is only two, and the hand value is 21, then the hand is a blackjack
		if (BlackjackHand::numCards == 2 && BlackjackHand::handValue == 21)
		{
			BlackjackHand::blackJack = true;
			BlackjackHand::stand = true;
		}
		else if (BlackjackHand::handValue > 21)
		{
			//If the hand is over 21 and there are aces
			if (BlackjackHand::numAces > 0)
			{
				int aces = BlackjackHand::numAces;

				//Loop through deacreasing the value by 10 until the value is less than 21 or all the aces have been changed to 1
				for (int i = 0; i < aces; i++)
				{
					BlackjackHand::handValue -= 10;
					BlackjackHand::numAces--;

					//Once hand value is 21, break out of the loop
					if (BlackjackHand::handValue < 21)
					{
						break;
					}
				}
			}
			else {
				//If there are no aces to decrease the hand value, the hand is a bust
				BlackjackHand::bust = true;
			}
		}
	}