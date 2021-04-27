#pragma once

#include "PlayingCard.h"


class BlackjackPlayer
{
private:

	int chips; //Number of chips available to bet with

public:
	
	BlackjackPlayer();

	BlackjackPlayer(int); //Adds number of chips player has

	int PlaceBet(); //Allows player to place a bet

	void AddCards(PlayingCard); //Adds a new card when dealt

	void Stand(); //Stands current hand

	void DisplayHand(); //Displays the cards in hand

	int GetHandValue(); //Returns value of hand

	void AddChips(int); //Recieves winnings and adds them to the players chips

	void ResetHand(); //Resets hand

	bool IsBlackjack(); 

	bool split;

	int GetChips() { return chips; } //Returns chips

};

