#pragma once

#include "player.h"
#include "carddeck.h"

class Controller {

private:
	Player		players[MAX_PLAYERS];
	CardDeck	cardDeck;
	int			numberOfPlayers;
	int			currentPlayer;
	Card		discardDeck[SUITS * CARDS - 1];
	Card		playerDiscardDeck[SUITS * CARDS - 1];
	int			discardNumber;
	int			playerDiscardNumber;
	int			currentCardNumber;

	void		nextCard();
	void		nextPlayer();

public:
	Controller();
	~Controller();

	void newGame(string playerNames[], int numberOfPlayers);

	bool gameIsInProgress();
	Card* getPlayersHand(int playerNumber);
	int getCardsLeft(int playerNumber);
	void play(int cardNumber);
	void turnFinished();
	int getNumberOfPlayers();
	int getCurrentPlayer();
	string getPlayerName(int playerNumber);
	string getCurrentCard();
	bool bullshit(int challenger);

	// FOR TEST PURPOSES ONLY
	Player getPlayer(int playerNumber);
};

