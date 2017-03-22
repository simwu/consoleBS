#pragma once

#include "card.h"

class CardDeck {

private:
	Card	cardDeck[SUITS][CARDS];
	int		numberOfCards;

public:
	CardDeck();
	~CardDeck();

	void shuffle();
	Card deal();
};

