#pragma once

#include "constants.h"
#include <string>
using namespace std;

class Card {

private:
	int suitNumber;
	int cardNumber;

public:
	Card();
	~Card();

	int getSuitNumber();
	int getCardNumber();
	void setSuitNumber(int suit);
	void setCardNumber(int card);

	string toString();
	string toGraphic();
};

