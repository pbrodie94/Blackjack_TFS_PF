#pragma once

#include "CardDeck.h"
#include "PlayingCard.h"

#include <iostream>

using namespace std;

class BlackjackDealer
{
public:

	BlackjackDealer() {};

	BlackjackDealer(int);

	void DealCards() {};

	//PlayingCard Hit();

private:

	void CreateDeck(int);

};

