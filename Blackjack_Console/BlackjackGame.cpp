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

	player.DisplayHand();
	//Display 1 dealer card and ? for the other

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
	bool turnNotDone = false;

	//Check if both beginning cards have the same value, if so offer split
	do {
		cout << "Type 'H' - to hit, 'S' - to stand: ";
		cin >> move;

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

			turnNotDone = false;
			break;

		case 'D':
			//Double Down
			turnNotDone = false;
			break;

		case 'P':
			//Split
			turnNotDone = true;
			break;

		default:
			cout << "\nInvalid entry, please try again. \n" << endl;
			
			turnNotDone = true;
			break;
		}

		if (player.GetHandValue() > 21)
		{
			cout << "BUST!\n" << endl;

			turnNotDone = false;
		}

	} while (turnNotDone);
}

void BlackjackGame::DealerTurn()
{
	dealer.TakeTurn();
	dealer.DisplayCards();

	do {

		dealer.AddCard(deck.DrawCard());
		dealer.DisplayCards();

	} while (dealer.GetHandValue() < 17);

}

void BlackjackGame::EndGame()
{
	if (player.GetHandValue() > 21)
	{
		//Lose
		cout << "\nHouse Wins.\n" << endl;
	}
	else if (dealer.GetHandValue() > player.GetHandValue() && dealer.GetHandValue() <= 21)
	{
		//Lose
		cout << "\nHouse Wins.\n" << endl;

	} else {

		if (player.GetHandValue() == dealer.GetHandValue())
		{
			cout << "\nPush, bet returned. \n" << endl;
			player.AddChips(playerBet);
		}
		else if (player.GetHandValue() > dealer.GetHandValue() || dealer.GetHandValue() > 21)
		{
			//win
			int winnings = 0;

			if (player.IsBlackjack())
			{
				cout << "\nBlackjack!\n" << endl;

				
				winnings = playerBet + (playerBet * 1.5);
				player.AddChips(winnings);
			}
			else {
				cout << "\nYou win!\n" << endl;

				winnings = playerBet * 2;
				player.AddChips(winnings);
			}
		}
	}
}