#include "player.h"

Player::Player() {
	name = "";
	cardsLeft = 0;
}

Player::~Player() {
}

string Player::getName() {
	return name;
}

void Player::setName(string name) {
	this->name = name;
}

void Player::draw(Card card) {
	playerHand[cardsLeft] = card;
	cardsLeft++;
}

Card Player::play(int cardNumber) {

	// Copy the Card to be removed
	Card card;
	card.setSuitNumber(playerHand[cardNumber - 1].getSuitNumber());
	card.setCardNumber(playerHand[cardNumber - 1].getCardNumber());

	// Remove the card played from the Player Hand
	shiftLeft(cardNumber);
	cardsLeft--;

	return card;
}

void Player::shiftLeft(int cardNumber) {

	for (int card = cardNumber; card <= cardsLeft; card++) {
		playerHand[card - 1] = playerHand[card];
	}
}

int Player::getCardsLeft() {
	return cardsLeft;
}

Card* Player::getPlayerHand() {
	return playerHand;
}

void Player::init() {
	name = "";

	for (int cardNumber = 0; cardNumber < SUITS * CARDS - 1; cardNumber++) {
		playerHand[cardNumber].setSuitNumber(NO_CARD);
		playerHand[cardNumber].setCardNumber(NO_CARD);
	}

	cardsLeft = 0;
}

