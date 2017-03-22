#include "view.h"

View::View(Controller &ctrl) : controller(ctrl) {
	// Get the Windows Console "handle" (reference)
#if defined _WIN32 || defined _WIN64
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

View::~View() {
}

void View::mainMenu() {

	int menuOption = 0;

	while (menuOption != 3) {

		cout << "Bullshit Menu" << endl << endl;
		cout << "1. New Game" << endl;
		cout << "2. Help!" << endl;
		cout << "3. Exit" << endl << endl;

		cout << "Enter your Menu option: ";
		cin >> menuOption;

		// Must do this each time you do cin into numeric variable!
		if (!cin.good()) {
			menuOption = 0;
		}

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		switch (menuOption) {

		case 1: {
			newGame();
			break;
		}
		case 2: {
			help();
			break;
		}
		case 3: {
			cout << endl << "Thank you for playing Bullshit!" << endl << endl;
			break;
		}
		default: {
			cout << endl << "Invalid Menu option." << endl << endl;
		}
		}
	}
}

void View::newGame() {

	// Get Player names and player count
	string playerNames[MAX_PLAYERS];
	int numberOfPlayers = getPlayerNames(playerNames);

	if (numberOfPlayers >= MIN_PLAYERS) {

		cout << endl << "This game will be a " << numberOfPlayers << "-player game." << endl << endl;

		// Tell the Controller to setup a new game
		controller.newGame(playerNames, numberOfPlayers);

		// Begin game play
		play();
	}
	else {
		cout << endl << "There must be at least " << MIN_PLAYERS << " players to play a game." << endl << endl;
	}
}

int View::getPlayerNames(string playerNames[]) {

	int numberOfPlayers = 0;

	cout << endl << "Enter 2-4 Player names. Press Enter when finished." << endl << endl;

	for (int player = 0; player < MAX_PLAYERS; player++) {
		cout << "Enter Player #" << (player + 1) << "'s name: ";
		getline(cin, playerNames[player]);

		// Need to trim leading and trailing spaces before checking the length

		if (playerNames[player].length() > 0) {
			numberOfPlayers++;
		}
		else {
			break;
		}
	}

	return numberOfPlayers;
}

void View::play() {

	// The Play Loop
	while (controller.gameIsInProgress()) {

		// Tell the current Player to play
		playCard();

		// Bullshit round: give other Players a chance to challenger
		bullshit();

		// Current Players' turn is finished
		controller.turnFinished();
	}

	// Announce the winner
	cout << controller.getPlayerName(controller.getCurrentPlayer()) << ", you're the winner!" << endl << endl;
}

void View::playCard() {

	int currentPlayer = controller.getCurrentPlayer();
	int cardsLeft = controller.getCardsLeft(currentPlayer);
	int cardsPlayed = 0;
	string number = "";
	int cardNumber = 0;

	while (cardsLeft > 0) {

		// Display the current Card to play
		cout << controller.getPlayerName(currentPlayer) << ", it's your turn to play " << controller.getCurrentCard() << "'s" << endl << endl;

		// Display the current Player's hand
		displayPlayerHand(currentPlayer);

		cout << endl << "Enter the number of the Card to play. Press Enter when finished: ";
		getline(cin, number);
		cout << endl;

		if (number.length() > 0) {
			try {
				cardNumber = stoi(number);

				if (cardNumber < 1 || cardNumber > cardsLeft) {
					cout << "Invalid Card number." << endl << endl;
				}
				else {
					// Tell the current Player to discard the Card played
					controller.play(cardNumber);
					cardsLeft = controller.getCardsLeft(currentPlayer);
					cardsPlayed++;
				}
			}
			catch (const invalid_argument& ia) {
				cout << "Invalid Card number." << endl << endl;
			}
		}
		else if (cardsPlayed == 0) {
			cout << "You must play at least one card!" << endl;
		}
		else {
			// Finished
			break;
		}
	}

	// Clear the screen
	clearScreen();
}

void View::help() {

	cout << endl << "Introduction" << endl;
	cout << "------------" << endl << endl;

	cout << "This game is generally called Cheat in Britain and Bullshit in the USA.In many books it appears as I Doubt It." << endl;
	cout << "The aim is to get rid of all your cards by playing them to a discard pile. Since cards are played face down," << endl;
	cout << "giving players the option to lie about the cards they are playing, but if the lie is exposed they must pick up the pile." << endl << endl;

	cout << "In this game each player plays the next rank above the previous player. Please note that there is another game," << endl;
	cout << "also known as I Doubt It or Bluff, in which all players are required to play the same rank until there is a challenger." << endl << endl;

	cout << "Players and Cards" << endl;
	cout << "-----------------" << endl << endl;

	cout << "The game can be played by from 2 to 10 players.One standard pack of 52 cards is used." << endl << endl;

	cout << "Play" << endl;
	cout << "----" << endl << endl;

	cout << "All the cards are dealt out to the players; some may have more than others, but not by much. The object is" << endl;
	cout << "to get rid of all your cards. Select at random who should go first and continue clockwise." << endl << endl;

	cout << "On the table is a discard pile, which starts empty. A turn consists of discarding one or more cards face down" << endl;
	cout << "on the pile, and calling out their rank. The first player must discard Aces, the second player discards Twos," << endl;
	cout << "the next player Threes, and so on. After Tens come Jacks, then Queens, then Kings, then back to Aces, etc." << endl << endl;

	cout << "Since the cards are discarded face down, you do not in fact have to play the rank you are calling. For example" << endl;
	cout << "if it is your turn to discard Sevens, you may actually discard any card or mixture of cards. If you donʹt have any Sevens" << endl;
	cout << "you will be forced to play some other card or cards." << endl << endl;

	cout << "Any player who suspects that the card(s) discarded by a player do not match the rank called can challenger the play" << endl;
	cout << "by calling Cheat!, Bullshit! or I doubt it! (depending on what you call the game). Then the cards played by the" << endl;
	cout << "challenged player are exposed and one of two things happens:" << endl << endl;

	cout << "1. If they are all of the rank that was called, the challenger is false, and the challenger must pick up" << endl;
	cout << "   the whole discard pile." << endl;
	cout << "2. If any of the played cards is different from the called rank, the challenger is correct, and the person who played" << endl;
	cout << "   the cards must pick up the whole discard pile." << endl << endl;

	cout << "After the challenger is resolved, play continues in normal rotation: the player to the left of the one who was challenged" << endl;
	cout << "plays and calls the next rank in sequence." << endl << endl;

	cout << "The first player to get rid of all their cards and survive any challenger resulting from their final play wins the game." << endl;
	cout << "If you play your last remaining card(s), but someone challenges you and the cards you played are not what you called," << endl;
	cout << "you pick up the pile and play continues." << endl << endl;
}

void View::bullshit() {

	int numberOfPlayers = controller.getNumberOfPlayers();
	int currentPlayer = controller.getCurrentPlayer();
	char choice = ' ';
	bool bull = false;
	bool challenge = false;

	for (int challenger = 1; challenger <= numberOfPlayers; challenger++) {

		if (challenger != currentPlayer) {
			// Display the challenger's hand
			displayPlayerHand(challenger);

			// Ask this Player to challege or pass
			choice = ' ';

			while (choice != 'B' && choice != 'P') {
				cout << controller.getPlayerName(challenger) << ", press B for Bullshit! or P for Pass: ";
				cin >> choice;

				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << endl;

				choice = toupper(choice);

				if (choice == 'B') {
					challenge = true;

					bull = controller.bullshit(challenger);

					if (bull) {
						cout << controller.getPlayerName(challenger) << " you won the challege!" << endl << endl;
					}
					else {
						cout << controller.getPlayerName(challenger) << " you lost the challege!" << endl << endl;
					}
				}
				else if (choice == 'P') {
					// Nothing to do - skip to the next challenger
				}
				else {
					cout << endl << "Invalid choice." << endl << endl;
				}
			}

			// Clear the screen
			clearScreen();
		}

		// If a challege has been made, we're done
		if (challenge) {
			break;
		}
	}
}

void View::clearScreen() {

	string text = "";
	cout << "Press Enter to erase the screen...";
	getline(cin, text);

#if defined _WIN32 || defined _WIN64
	std::system("cls");
#elif defined __linux || defined __APPLE__
	system("clear");
#elif
	// Generic way to "clear" the console window
	cout << string(1000, '\n');
#endif
}

void View::displayPlayerHand(int playerNumber) {
	Card *playerHand = controller.getPlayersHand(playerNumber);
	int cardsLeft = controller.getCardsLeft(playerNumber);

	cout << controller.getPlayerName(playerNumber) << "'s hand" << endl << endl;

	for (int card = 0; card < cardsLeft; card++) {
		cout << (card + 1) << ":\t" << playerHand[card].toGraphic() << endl;
	}

	cout << endl;
}



