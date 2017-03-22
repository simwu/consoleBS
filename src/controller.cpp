#include "controller.h"

Controller::Controller() {
	currentPlayer = 0;
	numberOfPlayers = 0;
	discardNumber = 0;
	playerDiscardNumber = 0;
	currentCardNumber = 0;
}

Controller::~Controller() {
}

void Controller::newGame(string playerNames[], int numberOfPlayers) {

	// Initialize each Player and give each Player its new name
	for (int playerNumber = 0; playerNumber < numberOfPlayers; playerNumber++) {
		players[playerNumber].init();
		players[playerNumber].setName(playerNames[playerNumber]);
	}

	this->numberOfPlayers = numberOfPlayers;
	currentPlayer = 1;

	// Initialize the Discard Decks
	for (int discard = 0; discard < SUITS * CARDS - 1; discard++) {
		discardDeck[discard].setSuitNumber(NO_CARD);
		discardDeck[discard].setCardNumber(NO_CARD);

		playerDiscardDeck[discard].setSuitNumber(NO_CARD);
		playerDiscardDeck[discard].setCardNumber(NO_CARD);
	}

	discardNumber = 0;
	playerDiscardNumber = 0;

	// Shuffle the card deck
	cardDeck.shuffle();

	// Deal each Player's hand
	for (int card = 1; card <= SUITS * CARDS; card++) {
		players[currentPlayer - 1].draw(cardDeck.deal());
		nextPlayer();
	}

	currentPlayer = 1;
	currentCardNumber = ACE;
}

void Controller::nextPlayer() {

	if (currentPlayer < numberOfPlayers) {
		currentPlayer++;
	}
	else {
		currentPlayer = 1;
	}
}

bool Controller::gameIsInProgress() {
	bool inProgress = true;

	for (int playerNumber = 0; playerNumber < numberOfPlayers; playerNumber++) {
		if (players[playerNumber].getCardsLeft() == 0) {
			inProgress = false;
			break;
		}
	}

	return inProgress;
}

Player Controller::getPlayer(int playerNumber) {
	return players[playerNumber - 1];
}

Card* Controller::getPlayersHand(int playerNumber) {
	return players[playerNumber - 1].getPlayerHand();
}

int Controller::getCardsLeft(int playerNumber) {
	return players[playerNumber - 1].getCardsLeft();
}

void Controller::play(int cardNumber) {
	playerDiscardDeck[playerDiscardNumber] = players[currentPlayer - 1].play(cardNumber);
	playerDiscardNumber++;
}

void Controller::turnFinished() {

	if (playerDiscardNumber > 0) {
		// No challege took place. Copy the Player Discard Deck to the Discard Deck
		for (int cardNumber = 0; cardNumber < playerDiscardNumber; cardNumber++) {

			discardDeck[discardNumber] = playerDiscardDeck[cardNumber];
			discardNumber++;

			// Clear the Card from the discard deck
			playerDiscardDeck[cardNumber].setSuitNumber(NO_CARD);
			playerDiscardDeck[cardNumber].setCardNumber(NO_CARD);
		}

		playerDiscardNumber = 0;
	}

	if (gameIsInProgress()) {
		nextPlayer();
		nextCard();
	}
}

int Controller::getNumberOfPlayers() {
	return numberOfPlayers;
}

int Controller::getCurrentPlayer() {
	return currentPlayer;
}

string Controller::getPlayerName(int playerNumber) {
	return players[playerNumber - 1].getName();
}

string Controller::getCurrentCard() {
	string currentCard = "";

	switch (currentCardNumber) {
	case ACE: {
		currentCard = "Ace";
		break;
	}
	case JACK: {
		currentCard = "Jack";
		break;
	}
	case QUEEN: {
		currentCard = "Queen";
		break;
	}
	case KING: {
		currentCard = "King";
		break;
	}
	default: {
		currentCard = to_string(currentCardNumber);
	}
	}

	return currentCard;
}

void Controller::nextCard() {

	if (currentCardNumber < KING) {
		currentCardNumber++;
	}
	else {
		currentCardNumber = ACE;
	}
}

bool Controller::bullshit(int challenger) {

	bool bull = false;

	// Check the Cards played by the current Player against the current play Card
	for (int cardNumber = 0; cardNumber < playerDiscardNumber; cardNumber++) {
		if (playerDiscardDeck[cardNumber].getCardNumber() != currentCardNumber) {
			bull = true;
			break;
		}
	}

	if (bull) {
		// Give the current Player all the Cards played so far
		for (int cardNumber = 0; cardNumber < playerDiscardNumber; cardNumber++) {
			players[currentPlayer - 1].draw(playerDiscardDeck[cardNumber]);

			// Clear the Card from the discard deck
			playerDiscardDeck[cardNumber].setSuitNumber(NO_CARD);
			playerDiscardDeck[cardNumber].setCardNumber(NO_CARD);
		}

		for (int cardNumber = 0; cardNumber < discardNumber; cardNumber++) {
			players[currentPlayer - 1].draw(discardDeck[cardNumber]);

			// Clear the Card from the discard deck
			discardDeck[cardNumber].setSuitNumber(NO_CARD);
			discardDeck[cardNumber].setCardNumber(NO_CARD);
		}
	}
	else {
		// Give the challenger Player all the Cards played so far
		for (int cardNumber = 0; cardNumber < playerDiscardNumber; cardNumber++) {
			players[challenger - 1].draw(playerDiscardDeck[cardNumber]);

			// Clear the Card from the discard deck
			playerDiscardDeck[cardNumber].setSuitNumber(NO_CARD);
			playerDiscardDeck[cardNumber].setCardNumber(NO_CARD);
		}

		for (int cardNumber = 0; cardNumber < discardNumber; cardNumber++) {
			players[challenger - 1].draw(discardDeck[cardNumber]);

			// Clear the Card from the discard deck
			discardDeck[cardNumber].setSuitNumber(NO_CARD);
			discardDeck[cardNumber].setCardNumber(NO_CARD);
		}
	}

	playerDiscardNumber = 0;
	discardNumber = 0;

	return bull;
}