#include "BlackjackGame.h"

BlackjackDealer dealer;
BlackjackPlayer player;

int playerBet = 0; //The players bet. When the player wins, they will recieve double this value back

BlackjackGame::BlackjackGame(int deckSize)
{
	cout << endl << "Initializing game..." << endl;

	dealer = BlackjackDealer(deckSize);
	player = BlackjackPlayer(1000, &dealer);

	StartRound();
}

void StartRound()
{
	playerBet = player.PlaceBet();

	dealer.DealCards();
}

void PlayGame()
{
	//Player takes turn

	//Dealer takes turn

	//If neither player or dealer busted, check who has the higher card value

	//If players chips are not 0, start new round
}