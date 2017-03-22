#pragma once

#include "card.h"
#include <string>
using namespace std;

class Player {

private:
	string	name;
	Card	playerHand[SUITS * CARDS - 1];
	int		cardsLeft;

	void	shiftLeft(int cardNumber);

public:
	Player();
	~Player();

	void init();
	string getName();
	void setName(string name);
	void draw(Card card);
	Card play(int cardNumber);
	int getCardsLeft();
	Card* getPlayerHand();
};

