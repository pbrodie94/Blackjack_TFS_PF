// Blackjack_Console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BlackjackGame.h"

using namespace std;

int main()
{
	BlackjackGame game; //Game object

	int deckSize = 1; //Number of decks
	bool loopAgain = true; //While loop condition

	//Welcome message
	cout << "Welcome to Blackjack! \n";

	do {
		//Get number of decks for game
		cout << "How many decks would you like to use? Please choose a number between 1 and 8 ";
		cin >> deckSize;

		//Check if valid deck size
		if (deckSize >= 1 && deckSize <= 8)
		{
			//Start game with decksize selection
			//game = BlackjackGame(deckSize);

			//Once game finishes, restart?
			string goSelection = "";
			cout << endl << "Game over, would you like to play again? type Y for yes, or any other key for no. ";
			cin >> goSelection;

			if (goSelection == "Y" || goSelection == "y")
			{
				loopAgain = true;
			}
			else {
				cout << endl << "Goodbye!";
				loopAgain = false;
			}
		}
		//Chose wrong deck size
		else {
			cout << endl << "Invalid deck size selection, please try again. " << endl;

			loopAgain = true;
		}


	} while (loopAgain);

	return 0;

}
