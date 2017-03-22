#include "DiceModel.h"
#include <time.h>			// time
#include <stdlib.h>			// srand, rand
#include <algorithm>		// sort
using namespace std;

DiceModel::DiceModel() {
	
	// Initialize the dice
	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
		dice[diceNumber] = 0;
	}

	// Seed (intialize) the random number generator
	srand(time(NULL));
}


DiceModel::~DiceModel() {

}

int* DiceModel::getDice() {

	return dice;
}

void DiceModel::setDice(int dice[]) {
	
	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
		this->dice[diceNumber] = dice[diceNumber];
	}
}

void DiceModel::roll() {

	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
		dice[diceNumber] = rand() % DICE_SIDES + 1;
	}
	sortDice();
}

void DiceModel::sortDice() {

	sort(dice, dice + NUMBER_OF_DICE);
}
