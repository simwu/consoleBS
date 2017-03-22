#include "View.h"
#include "Controller.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

View::View(Controller &cont) : controller(cont) {

}

View::~View() {

}

void View::displayMainMenu() {

	char menuOption = ' ';

	while (menuOption != 'X') {

		cout << "Game Menu" << endl << endl;

		cout << "N. New Game" << endl;
		cout << "I. Instructions" << endl;
		cout << "X. Exit" << endl << endl;

		cout << "Select a Game option: ";

		cin >> menuOption;

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << endl;

		// Convert to Menu option to upper case
		menuOption = toupper(menuOption);

		// Process the Player request
		switch (menuOption) {

			case 'N': {

				newGame();
				break;
			}
			case 'I': {

				instructions();
				break;
			}
			case 'X': {

				cout << "Thank you for playing RPS!" << endl << endl;
				break;
			}
			default: {

				cout << "Invalid Menu Option" << endl << endl;
				break;
			}
		}
	}
}

void View::newGame() {

	/*
	Initialize the Game
	*/

	cout << "New Game" << endl << endl;

	string playerNames[MAX_PLAYERS];

	
	// Get the Player names and the number of Players for this Game
	int numberOfPlayers = getPlayerNames(playerNames);

	cout << endl << "This will be a " << numberOfPlayers << "-Player match" << endl << endl;

	// Test
	for (int index = 0; index < numberOfPlayers; index++) {
		cout << "'" << playerNames[index] << "'" << " length = " << playerNames[index].length() << endl;
	}

	// Begin a new Game
	controller.newGame(numberOfPlayers, playerNames);
	

	// Begin plan
	play(playerNames);
	
}

int View::getPlayerNames(string playerNames[]) {

	int numberOfPlayers = 0;

	for (int index = 0; index < MAX_PLAYERS; index++) {

		cout << "Enter Player " << (index + 1) << " Name -or- press Enter to continue: ";

		getline(cin, playerNames[index]);

		playerNames[index] = trim(playerNames[index]);

		if (playerNames[index].length() > 0) {

			numberOfPlayers++;
		}
		else if (numberOfPlayers >= MIN_PLAYERS) {
			break;
		}
		else {

			cout << endl << "The minimum number of Players is " << MIN_PLAYERS << endl << endl;

			// Redo the loop turn
			index--;		
		}

	}

	for (int index = 0; index < numberOfPlayers; index++) {
		cout << endl << "'" << playerNames[index] << "'" << " length = " << playerNames[index].length() << endl;
	}

	return numberOfPlayers;
}

void View::play(string playerNames[]) {

	/*
	Game loop
	*/

	while (controller.isGameOver() == false) {

		// Get user input
		int playerMove = getPlayerMove(playerNames);

		// Update the game (controller)
		string weapon = controller.displayPlayerMove(playerMove);

		// Update the View
		cout << "Current Weapon: " << weapon << endl;
	}
}

int View::getPlayerMove(string playerNames[]) {
	
	int numberOfPlayers = 0;
	int index = 0;

	int playerMove = ' ';
	
	while (playerMove != '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9' || '0') {
		
		cout << endl;

		cout << "Weapon Options:" << endl;

		cout << "1. Sword" << endl;
		cout << "2. Spear" << endl;
		cout << "3. Axe" << endl;
		cout << "4. Light Saber" << endl;
		cout << "5. Gun" << endl;
		cout << "6. Bow" << endl;
		cout << "7. Tomahawk" << endl;
		cout << "8. Grenade" << endl;
		cout << "9. Flash Bang" << endl;
		cout << "0. Claymore" << endl << endl;

		cout << playerNames[index] << "'s move: ";

		cin >> playerMove;

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << endl;

		switch (playerMove) {
		
			case SWORD: {
			
				cout << "Acquired Sword" << endl << endl;
				break;
			}
			case SPEAR: {
			
				cout << "Acquired Spear" << endl << endl;
				break;
			}
			case AXE: {
	
				cout << "Acquired Axe" << endl << endl;
				break;
			}
			case LIGHTSABER: {
			
				cout << "Acquired Light Saber" << endl << endl;
				break;
			}
			case GUN: {
	
				cout << "Acquired Gun" << endl << endl;
				break;
			}
			case BOW: {
	
				cout << "Acquired Bow" << endl << endl;
				break;
			}
			case TOMAHAWK: {
		
				cout << "Acquired Tomahawk" << endl << endl;
				break;
			}
			case GRENADE: {

				cout << "Acquired Grenade" << endl << endl;
				break;
			}
			case FLASHBANG: {
		
				cout << "Acquired Flash Bang" << endl << endl;
				break;
			}
			case CLAYMORE: {
	
				cout << "Acquired Claymore" << endl << endl;
				break;
			}
			default: {
	
				cout << "Invalid weapon choice" << endl << "Please choose again" << endl << endl;
				break;
			}
		}
		return playerMove;
	}
}

void View::instructions() {

	cout << endl << "Instructions about RPS" << endl << endl;

	cout << "Players(s):  1 Player vs AI or 2 Players vs each other" << endl << endl;

	cout << "Instructions:  The player input one of the following weapon listed." << endl << "If the input has the advantage, the player wins." << endl << "If the input has the disadvantage, the player loses." << endl << "Any other outcome results in a draw." << endl << endl;

	cout << "Weapon Choices:  Sword, Spear, Axe, Light Saber, Gun, Bow, Tomahawk," << endl << "Grenade, Flash Bang, and Claymore" << endl << endl;

	cout << "Advantages:" << endl;

	cout << "Sword beats Axe, Grenade, and Flash Bang" << endl;

	cout << "Spear beats Sword, Grenade, and Claymore" << endl;

	cout << "Axe beats Spear, Bow, and Tomahawk" << endl;

	cout << "Light Saber beats Axe, Bow, and Tomahawk" << endl;

	cout << "Gun beats Sword, Spear, and Axe" << endl;

	cout << "Bow beats Sword, Spear, and Claymore" << endl;

	cout << "Tomahawk beats Gun, Bow, and Flash Bang" << endl;

	cout << "Grenade beats Light Saber, Gun, and Claymore" << endl;

	cout << "Flash Bang beats Light Saber, Gun, and Grenade" << endl;

	cout << "Claymore beats Light Saber, Tomahawk, and Flash Bang" << endl << endl << endl;
}

string View::trim(string text) {

	// Trim leading white spaces
	int startPos = text.find_first_not_of(" \t\n");

	if (startPos > 0) {
		text = text.substr(startPos);
	}

	// Trim trailing white spaces
	int endPos = text.find_last_not_of(" \t\n");

	if (endPos >= 0) {
		text = text.substr(0, endPos + 1);
	}
	else if (endPos < 0) {
		text = "";
	}

	return text;
}
/*
void View::displayVictory() {

	cout << "Victory!" << endl << endl;
	
	displayPlayAgain();
}

void View::displayDefeat() {

	cout << "Defeat!" << endl << endl;
	
	displayPlayAgain();
}

void View::displayTie() {

	cout << "Tie." << endl << endl;

	displayPlayAgain();
}


void View::displayPlayAgain(string playerNames) {

	char endOption = ' ';

	while (endOption != 'Y' || 'N') {

			cout << "Play again? (Y/N): ";

			cin >> endOption;

			cin.clear();
			cin.ignore(INT_MAX, '\n');

			cout << endl;

			endOption = toupper(endOption);

			switch (endOption) {

			case 'Y': {

				getPlayerMove(playerNames);
				break;
			}

			case 'N': {

				displayMainMenu();
				break;
			}
			default: {

				cout << "Invalid Option" << endl << endl;
				break;
			}
		}
	}
}
*/
