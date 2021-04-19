#include "BlackjackPlayer.h"

int chips = 0; //Number of chips available to the player to bet with

string cardOne = ""; //First card in hand
string cardTwo = ""; //Second card in hand
int cardValue = 0; //Value of cards in hand

BlackjackDealer *dealer = nullptr;

BlackjackPlayer::BlackjackPlayer(int startChips, BlackjackDealer *d)
{
	chips = startChips;
	dealer = d;
}

int PlaceBet()
{
	int bet = 0;

	//Display chips
	cout << endl << "Chips: " << chips << endl;

	//Ask how much to bet
	bool invalid = false;

	do {
		cout << "How much would you like to bet? ";
		cin >> bet;

		if (bet > chips || bet <= 0)
		{
			cout << endl << "Invalid bet, please try again" << endl;

			invalid = true;
		}
		else {

			invalid = false;
		}

	} while (invalid);

	//Subtract from chips
	chips -= bet;

	return bet;

}

void TakeTurn()
{
	char move;
	bool turnNotFinished = true;

	//Display cards in hand
	cout << endl << "Your hand is: " << cardOne << " and " << cardTwo << " and you're at " << cardValue << endl;

	do {

		cout << "Please enter: 'H' - Hit, 'S' - Stand: ";
		cin >> move;

		putchar(toupper(move));

		PlayingCard newCard = PlayingCard();

		switch (move)
		{

		case 'H':
			//Hit
			//Deal another card, display the name and add to the value

			//newCard = dealer->Hit();

			//Add the value of the newly drawn card
			//Print name of the newly drawn card, and the new card value

			if (cardValue > 21)
			{
				//Lose
				cout << endl << "BUST!" << endl;

				turnNotFinished = false;
			}
			else if (cardValue == 21)
			{
				//Max value, should not allow any more hits

				cout << endl << cardValue << "!" << endl;

				turnNotFinished = false;
			}
			else {

				//Under 21, ask the player what they'd like to do further

				turnNotFinished = true;
			}

			break;

		case 'S':

			//Turn finished

			turnNotFinished = false;

			break;

		default:
			cout << endl << "Invalid input, please try again.\n \n";

			turnNotFinished = true;

			break;
		}

	} while (turnNotFinished);

}
