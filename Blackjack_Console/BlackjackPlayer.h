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

	void TakeChips(int); //Takes chips without taking input

	void AddCards(PlayingCard); //Adds a new card when dealt

	void Stand(); //Stands current hand

	void Split(PlayingCard, PlayingCard); //Splits hand apart

	void DisplayHand(); //Displays the cards in hand

	int GetHandValue(int); //Returns value of hand

	void AddChips(int); //Recieves winnings and adds them to the players chips

	void ResetHand(); //Resets hand

	bool IsBlackjack(); //Getter to return whether the hand is a blackjack

	int GetChips() { return chips; } //Returns chips

	bool canSplit; //Is true if the player can split or not

	bool split; //Is true if the player has split

};

