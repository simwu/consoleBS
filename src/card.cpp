#include "card.h"

Card::Card() {
	suitNumber = NO_CARD;
	cardNumber = NO_CARD;
}

Card::~Card() {
}

int Card::getSuitNumber() {
	return suitNumber;
}

int Card::getCardNumber() {
	return cardNumber;
}

void Card::setSuitNumber(int suit) {
	suitNumber = suit;
}

void Card::setCardNumber(int card) {
	cardNumber = card;
}

string Card::toString() {

	string message = "";

	switch (cardNumber) {

	case ACE: {
		message = "Ace of ";
		break;
	}
	case 2: {
		message = "Two of ";
		break;
	}
	case 3: {
		message = "Three of ";
		break;
	}
	case 4: {
		message = "Four of ";
		break;
	}
	case 5: {
		message = "Five of ";
		break;
	}
	case 6: {
		message = "Six of ";
		break;
	}
	case 7: {
		message = "Seven of ";
		break;
	}
	case 8: {
		message = "Eight of ";
		break;
	}
	case 9: {
		message = "Nine of ";
		break;
	}
	case 10: {
		message = "Ten of ";
		break;
	}
	case JACK: {
		message = "Jack of ";
		break;
	}
	case QUEEN: {
		message = "Queen of ";
		break;
	}
	case KING: {
		message = "King of ";
		break;
	}
	}

	switch (suitNumber) {

	case SPADES: {
		message = message + "Spades";
		break;
	}
	case CLUBS: {
		message = message + "Clubs";
		break;
	}
	case HEARTS: {
		message = message + "Hearts";
		break;
	}
	case DIAMONDS: {
		message = message + "Diamonds";
		break;
	}
	}

	return message;
}

string Card::toGraphic() {

	string message = "";

	switch (cardNumber) {

	case ACE: {
		message = "A ";
		break;
	}
	case JACK: {
		message = "J ";
		break;
	}
	case QUEEN: {
		message = "Q ";
		break;
	}
	case KING: {
		message = "K ";
		break;
	}
	default: {
		message = "" + to_string(cardNumber) + " ";
		break;
	}
	}

	switch (suitNumber) {

	case HEARTS: {
		message = message + char(3);		// Windows only (3) Unicode ('\u2661')
		break;
	}
	case DIAMONDS: {
		message = message + char(4);		// Windows only (4) Unicode ('\u2662')
		break;
	}
	case CLUBS: {
		message = message + char(6);		// Windows only (6) Unicde ('\u2663')
		break;
	}
	case SPADES: {
		message = message + char(5);		// Windows only (5) Unicode ('\u2660')
		break;
	}
	}

	return message;
}










