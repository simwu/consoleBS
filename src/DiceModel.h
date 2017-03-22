#pragma once

#include "Constants.h"

class DiceModel {

	private:
		int dice[NUMBER_OF_DICE];

	public:
		DiceModel();
		~DiceModel();

		// Getters
		int* getDice();

		void roll();
		void sortDice();

		// FOR TEST PURPOSES ONLY
		void setDice(int dice[]);
};

