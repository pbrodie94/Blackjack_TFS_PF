#include "BlackjackGame.h"

#include "CardDeck.h"
#include "BlackjackPlayer.h"
#include "BlackjackDealer.h"

CardDeck deck;

BlackjackDealer dealer;
BlackjackPlayer player;

int playerBet = 0; //The players bet. When the player wins, they will recieve double this value back

BlackjackGame::BlackjackGame(int deckSize)
{
	cout << "\nInitializing game...\n" << endl;
	
	deck = CardDeck(deckSize);
	cout << "Deck created with " << deckSize * 52 << " cards shuffled...\n" << endl;

	player = BlackjackPlayer(1000);
	cout << "Added starting chips...\n" << endl;

	StartRound();
}

void BlackjackGame::StartRound()
{
	//Re-initialize both the Dealer and Player for a new round
	dealer = BlackjackDealer();
	player.ResetHand();

	//Prompt the player to place a bet
	playerBet = player.PlaceBet();

	//Dealing cards
	player.AddCards(deck.DrawCard());
	dealer.AddCard(deck.DrawCard());
	player.AddCards(deck.DrawCard());
	dealer.AddCard(deck.DrawCard());

	//Display 1 dealer card and ? for the other
	cout << "\nDealer Cards: ";
	dealer.DisplayCards();

	//Display the player's cards
	cout << "\n\nYour Cards: ";
	player.DisplayHand();
	cout << endl;

	PlayGame();
}

void BlackjackGame::PlayGame()
{
	//Player takes turn, player should not do anything if they have a Blackjack
	if (!player.IsBlackjack())
	{
		PlayerTurn();
	}

	//Dealer takes turn
	cout << "Dealer Turn: " << endl;
	DealerTurn();

	//Once both players have completed their turns, check the results
	EndGame();

	//If players chips are not 0, start new round
	if (player.GetChips() > 0)
	{
		StartRound();
	}
}

void BlackjackGame::PlayerTurn()
{
	char move = NULL;
	int numMoves = 0;
	bool secondHand = false;
	bool turnNotDone = false;

	//Check if both beginning cards have the same value, if so offer split
	do {
		//If the player's starting cards have the same value, give the option to split. Otherwise remove the option from the list
		//Also only offer double down on the first turn

		if (numMoves < 1)
		{
			//First move, allow double downs
			if (player.canSplit && !player.split)
			{
				cout << "Type 'H' - to hit, 'D' - to Double Down, 'P' - To Split, 'S' - to stand: ";
			}
			else {
				cout << "Type 'H' - to hit, 'D' - to Double Down, 'S' - to stand: ";
			}
		}
		else {
			cout << "Type 'H' - to hit, 'S' - to stand: ";
		}

		//Take in player input
		cin >> move;
		cout << endl;

		//Change player's input to uppercase
		move = toupper(move);

		switch (move)
		{
		case 'H':
			//Hit
			//Add a card to player's hand and display the result
			player.AddCards(deck.DrawCard());
			player.DisplayHand();

			turnNotDone = true;
			break;

		case 'S':
			//Stand
			player.Stand();

			//If the player has splut their hand, allow them to play their second hand
			if (player.split && !secondHand)
			{
				cout << "\nSecond Hand\n" << endl;

				secondHand = true;
				turnNotDone = true;
			}
			else {
				turnNotDone = false;
			}
			break;

		case 'D':
			//Double Down

			if (numMoves < 1)
			{
				//Check to make sure the player's chips allow for a double down
				if (player.GetChips() >= playerBet)
				{
					//If so, add another card
					player.AddCards(deck.DrawCard());
					//Double the player's bet
					player.TakeChips(playerBet);
					playerBet *= 2;

					//Display the new bet, then display the hand
					cout << "\nNew bet: $" << playerBet << "\n" << endl;
					player.DisplayHand();

					turnNotDone = false;
				}
				else {
					//Player does not have enough chips to double down
					cout << "\nNot enough chips! Please enter another action.\n" << endl;

					turnNotDone = true;
				}
			}
			else {
				//If the player is not able to double down
				cout << "\nCannot perform this action, please try another move.\n" << endl;

				turnNotDone = true;
			}
			break;

		case 'P':
			//Split
			//Double check that the player is able to split their hand
			if (player.canSplit && !player.split && player.GetChips() >= playerBet)
			{
				//Call the split method and add two more cards to fill out the two hands
				player.Split(deck.DrawCard(), deck.DrawCard());

				//Take double the player's bet for the second hand
				player.TakeChips(playerBet);
				playerBet *= 2;

				//Display the new bet amd the player's hand
				cout << "\nNew bet: $" << playerBet << "\n" << endl;
				player.DisplayHand();
			}
			else {
				//If the player is not able to split
				cout << "\nCannot perform this action, please try another move.\n" << endl;
			}

			turnNotDone = true;
			break;

		default:
			//Error catch for invalid entries
			cout << "\nInvalid entry, please try again. \n" << endl;
			
			turnNotDone = true;
			break;
		}

		//After each move, check to see if the player has bust
		if (player.GetHandValue(1) > 21 && !secondHand)
		{
			cout << "BUST!\n" << endl;
			
			//If the player has bust and they have split, allow them to play their second hand
			if (!player.split)
			{
				turnNotDone = false;
			}
			else {
				player.Stand();
				cout << "\nSecond Hand\n" << endl;
				secondHand = true;
				turnNotDone = true;
			}
		}

		//If player has split, check if their second hand has bust
		if (player.split && player.GetHandValue(2) > 21)
		{
			cout << "BUST!\n" << endl;
			player.Stand();
			turnNotDone = false;
		}

		numMoves++;

	} while (turnNotDone);
}

void BlackjackGame::DealerTurn()
{
	bool hitAgain = true;

	//Call the dealers take turn method, and display their cards
	dealer.TakeTurn();
	dealer.DisplayCards();

	//if the player has split, check both hands
	if (player.split)
	{
		if (player.GetHandValue(1) > 21 && player.GetHandValue(2) > 21)
		{
			hitAgain = false;
		}
	}
	else {
		if (player.GetHandValue(1) > 21)
		{
			hitAgain = false;
		}
	}

	while (hitAgain) {

		dealer.AddCard(deck.DrawCard());
		dealer.DisplayCards();

		//If player has split
		if (player.split)
		{
			//Check both hands to see what the dealer must beat
			if (player.GetHandValue(1) > player.GetHandValue(2))
			{
				if (dealer.GetHandValue() > 17 || dealer.GetHandValue() > player.GetHandValue(1))
				{
					hitAgain = false;
				}
				else {
					hitAgain = true;
				}
			}
			else {

				if (dealer.GetHandValue() > 17 || dealer.GetHandValue() > player.GetHandValue(2))
				{
					hitAgain = false;
				}
				else {
					hitAgain = true;
				}
			}
		}
		else {

			if (dealer.GetHandValue() > 17 || dealer.GetHandValue() > player.GetHandValue(1))
			{
				hitAgain = false;
			}
			else {
				hitAgain = true;
			}
		}
	}

}

void BlackjackGame::EndGame()
{
	int winnings = 0;
	int handResult = CheckWin(1);
	
	if (player.split)
	{
		playerBet /= 2;
	}

	switch (handResult)
	{
	case 0:
		//Lose
		cout << "\nHouse Wins.\n" << endl;

		break;

	case 1:
		//Push, return bet
		cout << "\nPush, bet returned. \n" << endl;
		player.AddChips(playerBet);

		break;

	case 2:
		//Win

		cout << "\nYou win!\n" << endl;

		winnings = playerBet * 2;
		player.AddChips(winnings);
		break;

	case 3:
		//Blackjack win

		cout << "\nBlackjack!\n" << endl;


		winnings = playerBet + (playerBet * 1.5);
		player.AddChips(winnings);
		break;
	}

	if (player.split)
	{
		handResult = CheckWin(2);

		switch (handResult)
		{
		case 0:
			//Lose
			cout << "\nHouse Wins.\n" << endl;

			break;

		case 1:
			//Push, return bet
			cout << "\nPush, bet returned. \n" << endl;
			player.AddChips(playerBet);

			break;

		case 2:
			//Win

			cout << "\nYou win!\n" << endl;

			winnings = playerBet * 2;
			player.AddChips(winnings);
			break;

		case 3:
			//Blackjack win

			cout << "\nBlackjack!\n" << endl;


			winnings = playerBet + (playerBet * 1.5);
			player.AddChips(winnings);
			break;
		}
	}
}

int BlackjackGame::CheckWin(int checkHand)
{
	//Return 0 for lose, 1 for push, 2 for win, 3 for blackjack win

	if (player.GetHandValue(checkHand) > 21)
	{
		//Lose
		return 0;
	}
	else if (dealer.GetHandValue() > player.GetHandValue(checkHand) && dealer.GetHandValue() <= 21)
	{
		//Lose
		return 0;

	}
	else {

		if (player.GetHandValue(checkHand) == dealer.GetHandValue())
		{
			return 1;
		}
		else if (player.GetHandValue(checkHand) > dealer.GetHandValue() || dealer.GetHandValue() > 21)
		{
			//win
			if (player.IsBlackjack())
			{
				return 3;
			}
			else {
				
				return 2;
			}
		}
	}
}