#pragma once

#if defined _WIN32 || defined _WIN64
#include <windows.h>				// Windows API header for console text colors
#elif defined __linux

#elif defined __APPLE__

#endif

#include "controller.h"
#include <iostream>
#include <string>
using namespace std;

class View {

private:
	Controller &controller;

#if defined _WIN32 || defined _WIN64
	HANDLE hConsole;
#endif

	void newGame();
	int getPlayerNames(string playerNames[]);
	void play();
	void help();
	void playCard();
	void bullshit();
	void clearScreen();
	void displayPlayerHand(int playerNumber);

public:
	View(Controller &ctrl);
	~View();

	void mainMenu();
};

