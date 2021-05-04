// Blackjack_Console.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "BlackjackGame.h"

using namespace std;

void DisplayInstructions();

int main()
{
	int deckSize = 1; //Number of decks
	bool loopAgain = true; //While loop condition

	//Welcome message
	cout << "Welcome to Blackjack! \n" << endl;

	do {
		//Get number of decks for game
		cout << "How many decks would you like to use? \n- Please choose a number between 1 and 8 \n- 0 for instructions \n- -1 or lower to quit" << endl;
		cout << "\n > ";
		cin >> deckSize;

		if (!cin.fail())
		{
			//Check if valid deck size
			if (deckSize >= 1 && deckSize <= 8)
			{
				//Start game with decksize selection
				BlackjackGame game = BlackjackGame(deckSize);

				//Once game over, restart?
				char goSelection;

				cout << "\nGame over, would you like to play again? type Y for yes, or any other key for no. ";
				cin >> goSelection;

				toupper(goSelection);

				if (goSelection == 'Y')
				{
					loopAgain = true;
				}
				else {
					cout << "\nGoodbye!" << endl;
					loopAgain = false;
				}
			}
			else if (deckSize == 0)
			{
				//Show instructions
				DisplayInstructions();

				loopAgain = true;
			}
			else if (deckSize < 0)
			{
				//goodbye message
				cout << "\nGoodbye!" << endl;

				loopAgain = false;
			}
			//Chose wrong deck size
			else {
				cout << "\nInvalid deck size selection, please try again. " << endl;

				loopAgain = true;
			}
		}
		else {
			cout << "\nInvalid entry, please input a number.\n" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			loopAgain = true;
		}

	} while (loopAgain);

	return 0;

}

void DisplayInstructions()
{
	//Display instructions
	cout << "\nBlackjack Instructions\n" << endl;

	cout << "The object of Blackjack is to get your hand's value as close to 21 as possible without going over as well as have a higher hand value than the dealer.\n" << endl;

	cout << "- The game begins with a round of betting. You may bet as much as you like provided you have enough chips" << endl;
	cout << "- The dealer will then deal two face up cards to you, and one face up and one face down card to the dealer" << endl;

	cout << "\nCard values are as follows: " << endl;
	cout << "- Numbered cards (2 - 9) are worth the amount that they display" << endl;
	cout << "- Ace can be 1 or 11. If the overall hand value is higher than 21 while the Ace is 11, its value becomes 1" << endl;
	cout << "- Face cards (Jack, Queen, King) are worth 10" << endl;
	cout << "- If you receive an Ace and a Face card on your starting hand, then you have a Blackjack!" << endl;

	cout << "\nDuring your turn you may perform the following actions:" << endl;
	cout << "- 'H' to Hit - Request another card. You may do this until you're at an acceptable value, or you exceed 21" << endl;
	cout << "- 'S' to Stand - When you're happy with your hand value, use stand" << endl;
	cout << "- 'D' to Double Down - If you're feeling good about your hand, you may double your bet and get one more card. This can only be done at the start of your turn." << endl;
	cout << "- 'P' to Split - If your intitial two cards are the same value (i.e. two Aces) you may split your hand into two and bet the same bet on the second" << endl;

	cout << "\nAt the end of the round:" << endl;
	cout << "- If your hand value is greater than the dealer, you win double your bet!" << endl;
	cout << "- If you get a Blackjack on your starting hand, you win your bet plus 1.5x your bet!" << endl;
	cout << "- If you and the dealer tie, this is known as a 'Push' and you will receive your bet back to play another round" << endl;
	cout << "- If your hand value is lesser than the dealer, or over 21, you lose the hand" << endl;

	cout << "\nGood Luck!\n" << endl;
}
