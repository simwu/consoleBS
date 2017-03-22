#include "PlayerHandModel.h"


PlayerHandModel::PlayerHandModel() {

	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
		handDice[diceNumber] = false;
	}

	for (int scoreNumber = 0; scoreNumber < NUMBER_OF_SCORES; scoreNumber++) {
		scoreCard[scoreNumber] = 0;
	}
	handScore		= 0;
	totalOfScores	= 0;
	handType		= NO_HAND;
}

PlayerHandModel::~PlayerHandModel() {

}

bool PlayerHandModel::isHandPlayed(int hand) {
	
	// If 0, has not been played
	return scoreCard[hand] != 0;
}

void PlayerHandModel::setDiceToRoll(bool diceToRoll[]) {

}

void PlayerHandModel::playHand(int hand) {
	scoreCard[hand] = handScore;
}


void PlayerHandModel::roll() {

	diceModel.roll();

	if (scoreCard[YAHTZEE] == 0 && !hasYahtzeePattern()) {
		
		if (scoreCard[LARGE_STRAIGHT] == 0 && !hasLargeStraightPattern()) {
		
			if (scoreCard[SMALL_STRAIGHT] == 0 && !hasSmallStraightPattern()) {

				if (scoreCard[FOUR_OF_A_KIND] == 0 && !hasFourOfAKindPattern()) {
					
					if (scoreCard[FULL_HOUSE] == 0 && !hasFullHousePattern()) {

						if (scoreCard[THREE_OF_A_KIND] == 0 && !hasThreeOfAKindPattern()) {
				
							if (scoreCard[SIXES] == 0 && !hasSixes()) {
									
								if (scoreCard[FIVES] == 0 && !hasFives()) {

									if (scoreCard[FOURS] == 0 && !hasFours()) {

										if (scoreCard[THREES] == 0 && !hasThrees()) {

											if (scoreCard[TWOS] == 0 && !hasTwos()) {

												if (scoreCard[ACES] == 0 && !hasAces()) {
															
													if (scoreCard[CHANCE] == 0) {
															
														chance();
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

// To help check and clear the COMBO functions so the boolean is not TTTT or FFFF leftover
void PlayerHandModel::initHand() {

	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
		handDice[diceNumber] = false;
	}
	handScore	= 0;
	handType	= NO_HAND;
}

// DICE COMBINATIONS
bool PlayerHandModel::hasYahtzeePattern() {

	initHand();

	int *dice = diceModel.getDice();
	
	bool yahtzee = (dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4]);

	if (yahtzee) {
		for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
			handDice[diceNumber] = true;
		}
		handScore			= 50;
		scoreCard[YAHTZEE]	= 50;
		totalOfScores		= totalOfScores + 50;
		handType			= YAHTZEE;
	}
	return yahtzee;
}

bool PlayerHandModel::hasLargeStraight() {
	
	initHand();

	bool largeStraight	= true;

	int *dice			= diceModel.getDice();
	int initialValue	= dice[0];

	for (int diceNumber = 1; diceNumber < NUMBER_OF_DICE; diceNumber++) {
		if (dice[diceNumber] != initialValue + 1) {

			largeStraight = false;
			// Finished
			diceNumber = NUMBER_OF_DICE;
		}
		else {
			initialValue++;
		}
	}
	if (largeStraight) {
		for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
			handDice[diceNumber] = true;
		}
		handScore					= 40;
		scoreCard[LARGE_STRAIGHT]	= 40;
		totalOfScores				= totalOfScores + 40;
		handType					= LARGE_STRAIGHT;
	}
	return largeStraight;
}

bool PlayerHandModel::hasLargeStraightPattern() {

	initHand();

	int *dice = diceModel.getDice();

	bool largeStraight = ((dice[0] == 1 && dice[1] == 2 && dice[2] == 3 && dice[3] == 4 && dice[4] == 5) ||
						(dice[0] == 2 && dice[1] == 3 && dice[2] == 4 && dice[3] == 5 && dice[4] == 6));

	if (largeStraight) {
		for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
			handDice[diceNumber] = true;
		}
		handScore					= 40;
		scoreCard[LARGE_STRAIGHT]	= 40;
		totalOfScores				= totalOfScores + 40;
		handType					= LARGE_STRAIGHT;
	}
	return largeStraight;
}


bool PlayerHandModel::hasSmallStraight() {

	initHand();

	bool smallStraight	= false;
	handDice[0]			= true;
	int *dice			= diceModel.getDice();

	int numberOfDice	= 1;
	int handDiceIndex	= 1;
	int nextValue		= dice[0] + 1;

	for (int diceNumber = 1; diceNumber < NUMBER_OF_DICE; diceNumber++) {

		if (dice[diceNumber] == nextValue) {

			handDice[handDiceIndex] = true;
			numberOfDice++;
		}
		// Check for gap
		else if (diceNumber == 1 && dice[diceNumber] > nextValue) {
			handDice[handDiceIndex - 1] = false;
			handDice[handDiceIndex] = true;
		}
		handDiceIndex++;
		nextValue = dice[diceNumber] + 1;
	}
	if (numberOfDice == 4) {
		handScore					= 30;
		scoreCard[SMALL_STRAIGHT]	= 30;
		totalOfScores				= totalOfScores + 30;
		handType					= SMALL_STRAIGHT;
		smallStraight	= true;
	}
	return smallStraight;
}

bool PlayerHandModel::hasSmallStraightPattern() {

	initHand();

	int *dice = diceModel.getDice();

	bool smallStraight = ((dice[0] == 1 && dice[1] == 2 && dice[2] == 3 && dice[3] == 4) ||
						  (dice[0] == 2 && dice[1] == 3 && dice[2] == 4 && dice[3] == 5) ||
						  (dice[0] == 3 && dice[1] == 4 && dice[2] == 5 && dice[3] == 6));

	if (smallStraight) {
		for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE - 1; diceNumber++) {
			handDice[diceNumber] = true;
		}

		handDice[4] = false;

		handScore					= 30;
		scoreCard[SMALL_STRAIGHT]	= 30;
		totalOfScores				= totalOfScores + 30;
		handType					= SMALL_STRAIGHT;
	}
	return smallStraight;
}

bool PlayerHandModel::hasFourOfAKindPattern() {
	
	initHand();

	bool fourOfAKind = false;

	int *dice = diceModel.getDice();

	if (dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3]) {
		for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE - 1; diceNumber++) {
			handDice[diceNumber] = true;
		}
		handType = FOUR_OF_A_KIND;
		fourOfAKind = true;
	}
	else if (dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4]) {
		for (int diceNumber = 1; diceNumber < NUMBER_OF_DICE; diceNumber++) {
			handDice[diceNumber] = true;
		}
		handType = FOUR_OF_A_KIND;
		fourOfAKind = true;
	}
	// Adds all 5 dice.  Ask the Player first.  Do not add the hand score to the score card or the total yet
	if (fourOfAKind) {
		for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
			handScore = handScore + dice[diceNumber];	
		}
	}
	return fourOfAKind;
}

bool PlayerHandModel::hasFullHousePattern() {
	
	initHand();

	bool fullHouse = hasTwoPairPattern();

	if (fullHouse) {

		// Save Two Pair Hand Dice
		bool twoPairHandDice[NUMBER_OF_DICE];
		// Copying class variable (handDice) to twoPaidHandDice
		copy(handDice, handDice + NUMBER_OF_DICE, twoPairHandDice);

		fullHouse = hasThreeOfAKindPattern();

		if (fullHouse) {

			// Merge the Two Pair and Three of a Kind hand dice by OR (|)
			for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
				handDice[diceNumber] = handDice[diceNumber] | twoPairHandDice[diceNumber];		
			// | = Adding Or(s) T/F
			}
			handType = FULL_HOUSE;
		}
		else {
			// Reversing the save of the Two Pair Hand Dice
			copy(twoPairHandDice, twoPairHandDice + NUMBER_OF_DICE, handDice);
		}
	}
	handScore				= 25;
	scoreCard[FULL_HOUSE]	= 25;
	totalOfScores			= totalOfScores + 25;
	return fullHouse;
}

bool PlayerHandModel::hasThreeOfAKindPattern() {

	initHand();

	bool threeOfAKind = false;

	int *dice = diceModel.getDice();

	if (dice[0] == dice[1] && dice[1] == dice[2]) {
		for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE - 2; diceNumber++) {
			handDice[diceNumber] = true;
		}
		handType = THREE_OF_A_KIND;
		threeOfAKind = true;
	}
	else if (dice[1] == dice[2] && dice[2] == dice[3]) {
		for (int diceNumber = 1; diceNumber < NUMBER_OF_DICE - 1; diceNumber++) {
			handDice[diceNumber] = true;
		}
		handType = THREE_OF_A_KIND;
		threeOfAKind = true;
	}
	else if (dice[2] == dice[3] && dice[3] == dice[4]) {
		for (int diceNumber = 2; diceNumber < NUMBER_OF_DICE; diceNumber++) {
			handDice[diceNumber] = true;
		}
		handType = THREE_OF_A_KIND;
		threeOfAKind = true;
	}
	// Adds all 5 dice.  Ask the Player first.  Do not add the hand score to the score card or the total yet
	if (threeOfAKind) {
		for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
			handScore = handScore + dice[diceNumber];
		}
	}
	return threeOfAKind;
}

bool PlayerHandModel::hasTwoPairPattern() {

	bool twoPair = false;

	int *dice = diceModel.getDice();

	if (dice[1] == dice[2] && dice[3] == dice[4]) {
		for (int diceNumber = 1; diceNumber < NUMBER_OF_DICE; diceNumber++) {
			handDice[diceNumber] = true;
		}
		// handType = TWO_PAIR;
		twoPair = true;
	}
	else if (dice[0] == dice[1] && dice[3] == dice[4]) {
		handDice[0] = true;
		handDice[1] = true;
		handDice[3] = true;
		handDice[4] = true;

		// handType	= TWO_PAIR;
		twoPair		= true;
	}
	else if (dice[0] == dice[1] && dice[2] == dice[3]) {
		for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE - 1; diceNumber++) {
			handDice[diceNumber] = true;
		}
		// handType = TWO_PAIR;
		twoPair = true;
	}
	return twoPair;
}

bool PlayerHandModel::hasOnePairPattern() {
	
	initHand();

	bool pair = false;

	int *dice = diceModel.getDice();

	if (dice[0] == dice[1]) {
		for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE - 3; diceNumber++) {
			handDice[diceNumber] = true;
		}
		// handType = ONE_PAIR;
		pair = true;
	}
	else if (dice[1] == dice[2]) {
		for (int diceNumber = 1; diceNumber < NUMBER_OF_DICE - 2; diceNumber++) {
			handDice[diceNumber] = true;
		}
		// handType = ONE_PAIR;
		pair = true;
	}
	else if (dice[2] == dice[3]) {
		for (int diceNumber = 2; diceNumber < NUMBER_OF_DICE - 1; diceNumber++) {
			handDice[diceNumber] = true;
		}
		// handType = ONE_PAIR;
		pair = true;
	}
	else if (dice[3] == dice[4]) {
		for (int diceNumber = 3; diceNumber < NUMBER_OF_DICE; diceNumber++) {
			handDice[diceNumber] = true;
		}
		// handType = ONE_PAIR;
		pair = true;
	}
	return pair;
}

bool PlayerHandModel::hasAces() {
	
	initHand();

	int*dice = diceModel.getDice();

	bool acesFound = false;

	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
		
		if (dice[diceNumber] == 1) {

			// Ask the Player first.  Do not add the hand score to the score card or the total yet
			handDice[diceNumber] = true;
			handScore		     = handScore + 1;
			acesFound			 = true;
		}
	}
	if (acesFound && handScore > 1) {
		handType = ACES;
	}
		else {
		handScore = 0;
		acesFound = false;
	}
	return acesFound;
}

bool PlayerHandModel::hasTwos() {

	initHand();

	int*dice = diceModel.getDice();

	bool twosFound = false;

	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {

		if (dice[diceNumber] == 2) {

			// Ask the Player first.  Do not add the hand score to the score card or the total yet
			handDice[diceNumber] = true;
			handScore			 = handScore + 2;
			twosFound			 = true;
		}
	}
	if (twosFound && handScore > 2) {
		handType = TWOS;
	}
	else {
		handScore = 0;
		twosFound = false;
	}
	return twosFound;
}

bool PlayerHandModel::hasThrees() {

	initHand();

	int*dice = diceModel.getDice();

	bool threesFound = false;

	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {

		if (dice[diceNumber] == 3) {
			
			// Ask the Player first.  Do not add the hand score to the score card or the total yet
			handDice[diceNumber] = true;
			handScore			 = handScore + 3;
			threesFound			 = true;
		}
	}
	if (threesFound && handScore > 3) {
		handType = THREES;
	}
	else {
		handScore = 0;
		threesFound = false;
	}
	return threesFound;
}

bool PlayerHandModel::hasFours() {

	initHand();

	int*dice = diceModel.getDice();

	bool foursFound = false;

	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {

		if (dice[diceNumber] == 4) {

			// Ask the Player first.  Do not add the hand score to the score card or the total yet
			handDice[diceNumber] = true;
			handScore			 = handScore + 4;
			foursFound			 = true;
		}
	}
	if (foursFound && handScore > 4) {
		handType = FOURS;
	}
	else {
		handScore = 0;
		foursFound = false;
	}
	return foursFound;
}

bool PlayerHandModel::hasFives() {

	initHand();

	int*dice = diceModel.getDice();

	bool fivesFound = false;

	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {

		if (dice[diceNumber] == 5) {

			// Ask the Player first.  Do not add the hand score to the score card or the total yet
			handDice[diceNumber] = true;
			handScore			 = handScore + 5;
			fivesFound			 = true;
		}
	}
	if (fivesFound && handScore > 5) {
		handType = FIVES;
	}
	else {
		handScore = 0;fivesFound = false;
		fivesFound = false;
	}
	return fivesFound;
}

bool PlayerHandModel::hasSixes() {

	initHand();

	int*dice = diceModel.getDice();

	bool sixesFound = false;

	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {

		if (dice[diceNumber] == 6) {

			// Ask the Player first.  Do not add the hand score to the score card or the total yet
			handDice[diceNumber] = true;
			handScore			 = handScore + 6;
			sixesFound			 = true;
		}
	}
	if (sixesFound && handScore > 6) {
		handType = SIXES;
	}
	else {
		handScore = 0;
		sixesFound = false;
	}
	return sixesFound;
}

void PlayerHandModel::chance() {

	initHand();

	int *dice = diceModel.getDice();

	for (int diceNumber = 0; diceNumber < NUMBER_OF_DICE; diceNumber++) {
		handScore = handScore + dice[diceNumber];
		handDice[diceNumber] = true;
	}
	handType = CHANCE;
}


DiceModel PlayerHandModel::getDiceModel() {
	return diceModel;
}

int PlayerHandModel::getHandType() {
	return handType;
}

int	PlayerHandModel::getHandScore() {
	return handScore;
}

int* PlayerHandModel::getScoreCard() {
	return scoreCard;
}

int	PlayerHandModel::getTotalOfScores() {
	return totalOfScores;
}

bool* PlayerHandModel::getHandDice() {
	return handDice;
}

// FOR TEST PURPOSES ONLY
void PlayerHandModel::setDice(int dice[]) {
	diceModel.setDice(dice);
}
