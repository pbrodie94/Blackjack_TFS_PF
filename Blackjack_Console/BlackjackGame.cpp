#include "BlackjackGame.h"

#include "CardDeck.h"
#include "BlackjackPlayer.h"

CardDeck deck;

//BlackjackDealer dealer;
BlackjackPlayer player;

int playerBet = 0; //The players bet. When the player wins, they will recieve double this value back

BlackjackGame::BlackjackGame(int deckSize)
{
	cout << endl << "Initializing game..." << endl;
	
	deck = CardDeck(deckSize);
	player = BlackjackPlayer(1000);

	StartRound();
}

void BlackjackGame::StartRound()
{
	playerBet = player.PlaceBet();

	//Dealing cards
	player.AddCards(deck.DrawCard());
	//Deal to Dealer
	player.AddCards(deck.DrawCard());

	player.DisplayHand();
	//Display 1 dealer card and ? for the other

	PlayGame();
}

void BlackjackGame::PlayGame()
{
	//Player takes turn
	PlayerTurn();

	//Dealer takes turn
	DealerTurn();

	//If neither player or dealer busted, check who has the higher card value

	//If players chips are not 0, start new round
}

void BlackjackGame::PlayerTurn()
{
	char move = NULL;
	bool turnNotDone = false;

	//Check if both beginning cards have the same value, if so offer split
	do {
		cout << "Type 'H' - to hit, 'S' - to stand, 'D' - to Double Down: ";
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
			turnNotDone = false;
			break;

		case 'D':
			//Double Down
			turnNotDone = true;
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

	} while (turnNotDone);
}

void BlackjackGame::DealerTurn()
{

}