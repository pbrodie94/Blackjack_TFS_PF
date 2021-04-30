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
	dealer = BlackjackDealer();
	player.ResetHand();

	playerBet = player.PlaceBet();

	//Dealing cards
	player.AddCards(deck.DrawCard());
	dealer.AddCard(deck.DrawCard());
	player.AddCards(deck.DrawCard());
	dealer.AddCard(deck.DrawCard());

	//Display 1 dealer card and ? for the other
	cout << "\nDealer Cards: ";
	dealer.DisplayCards();

	cout << "\n\nYour Cards: ";
	player.DisplayHand();
	cout << endl;

	PlayGame();
}

void BlackjackGame::PlayGame()
{
	//Player takes turn
	if (!player.IsBlackjack())
	{
		PlayerTurn();
	}

	//Dealer takes turn
	cout << "Dealer Turn: " << endl;
	DealerTurn();

	//If neither player or dealer busted, check who has the higher card value
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
	bool secondHand = false;
	bool turnNotDone = false;

	//Check if both beginning cards have the same value, if so offer split
	do {
		if (player.canSplit && !player.split)
		{
			cout << "Type 'H' - to hit, 'D' - to Double Down, 'P' - To Split, 'S' - to stand: ";
		}
		else {
			cout << "Type 'H' - to hit, 'D' - to Double Down, 'S' - to stand: ";
		}
		cin >> move;
		cout << endl;

		move = toupper(move);

		switch (move)
		{
		case 'H':
			//Hit
			player.AddCards(deck.DrawCard());
			player.DisplayHand();

			turnNotDone = true;
			break;

		case 'S':
			//Stand
			player.Stand();

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

			if (player.GetChips() >= playerBet)
			{
				player.AddCards(deck.DrawCard());
				player.TakeChips(playerBet);
				playerBet *= 2;

				cout << "\nNew bet: $" << playerBet << "\n" << endl;
				player.DisplayHand();

				turnNotDone = false;
			}
			else {

				cout << "\nNot enough chips! Please enter another action.\n" << endl;

				turnNotDone = true;
			}
			
			break;

		case 'P':
			//Split

			if (player.canSplit && !player.split && player.GetChips() >= playerBet)
			{
				player.Split(deck.DrawCard(), deck.DrawCard());

				player.TakeChips(playerBet);
				playerBet *= 2;

				cout << "\nNew bet: $" << playerBet << "\n" << endl;
				player.DisplayHand();
			}
			else {
				cout << "\nCannot perform this action, please try another move.\n" << endl;
			}

			turnNotDone = true;
			break;

		default:
			cout << "\nInvalid entry, please try again. \n" << endl;
			
			turnNotDone = true;
			break;
		}

		if (player.GetHandValue(1) > 21 && !secondHand)
		{
			cout << "BUST!\n" << endl;
			
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

		if (player.split && player.GetHandValue(2) > 21)
		{
			cout << "BUST!\n" << endl;
			player.Stand();
			turnNotDone = false;
		}

	} while (turnNotDone);
}

void BlackjackGame::DealerTurn()
{
	bool hitAgain = true;

	dealer.TakeTurn();
	dealer.DisplayCards();

	if (player.GetHandValue(1) > 21)
	{
		hitAgain = false;
	}

	while (hitAgain) {

		dealer.AddCard(deck.DrawCard());
		dealer.DisplayCards();

		if (dealer.GetHandValue() > 17 || dealer.GetHandValue() > player.GetHandValue(1))
		{
			hitAgain = false;
		}
		else {
			hitAgain = true;
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