#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int repetitions = 10000000;
int boardLength = 101;
int newPosition = 0;
int rollPath[100000];
int tempRollPath[1000];
int rollHistory[1000];
int gameBoard[101] = { 0 };
int minRoutes = 0;
int gameSquareCounter[101] = { 0 };
int snakesLadders[19][2] = {
	{ 1, 37 },
	{ 4, 10 },
	{ 9, 22 },
	{ 21, 21 },
	{ 28, 56 },
	{ 36, 8 },
	{ 51, 16 },
	{ 71, 20 },
	{ 80, 20 },
	{ 87, -63 }, 
	{ 16, -10 },
	{ 47, -21 },
	{ 49, -38 },
	{ 56, -3 },
	{ 62, -43 },
	{ 64, -4 },
	{ 93, -20 },
	{ 95, -20 },
	{ 98, -20 },
};
int minRolls = 0;
long float dieRollsAdder = 0;
int i = 0;

int rollDie(){
	//Roll DICE
	int diceroll = rand() % 6 + 1;
	/* Intializes random number generator */	
	
	return diceroll;
};

int initGameBoard(){
	for (int i = 0; i < 19; i++){
		gameBoard[snakesLadders[i][0]] = snakesLadders[i][1];
	}
}

int playGame() {
	//The game
	int position = 0, dieRolls = 0;

	while (position < 100){
		newPosition = position + rollDie();

		//Ensure the user never goes over 100
		if (newPosition <= 100){
			position = newPosition + gameBoard[newPosition];
			gameSquareCounter[position]++;
		};

		if (dieRolls <= minRolls){
			tempRollPath[dieRolls] = position;
		};

		dieRolls++;
		dieRollsAdder++;

		//Squares 1 - 94
		while (position <= 94){

			position = position + rollDie();
			position = position + gameBoard[position];
			gameSquareCounter[position]++;

			if (dieRolls <= minRolls){
				tempRollPath[dieRolls] = position;
			};

			dieRolls++;
			dieRollsAdder++;
		};
	};

	rollHistory[dieRolls]++;

	if (minRolls == 0) {
		minRolls = dieRolls;
	} else if (dieRolls < minRolls){
		minRoutes = 0;
		minRolls = dieRolls;
		for (i = 0; i < 1000; i++){
			if (rollPath[i] == 0){
				i = 1000;
			} else {
				rollPath[i] = 0;
			};
		};
	} else if (dieRolls == minRolls){

		int diff = 0;
		int j = 0;
		int uniqueRoute = 1;

		for (i = 0; i <= (minRoutes * minRolls); i = i + minRolls){
			j = 0;
			if (rollPath[i] == 0){
				diff = i;
				i = (minRoutes * minRolls) + 1;
			} else {
				while (j < minRolls && uniqueRoute == 1){
					if (rollPath[i + j] == tempRollPath[j]){
						j++;
						if (j == minRolls){
							uniqueRoute = 0;
						};
					} else {
						j = minRolls;
					};
				};
			};
		};

		if (uniqueRoute == 1){
			minRoutes++;
			for (i = 0; i < minRolls; i++){
				rollPath[i + diff] = tempRollPath[i];
			};
		};
	};
}

int stats(){
	int meanDieRolls = 0;
	float probabilitySquareC = 0;
	float probabilitySquareD = 0;
	int common = 0;
	int uncommon = 0;
	int popular = 0;
	//Find most popular Square
	for (i = 0; i <= 100; i++){
		if (gameSquareCounter[i] > gameSquareCounter[common]){
			common = i;
		};
		if ((gameSquareCounter[i] < gameSquareCounter[uncommon] || gameSquareCounter[uncommon] == 0) && gameSquareCounter[i] != 0){
			uncommon = i;
		}
	};

	for (i = 0; i < 1000; i++){
		if (rollHistory[i] > rollHistory[popular]){
			popular = i;
		}
	}

	probabilitySquareC = gameSquareCounter[common] * 100 / dieRollsAdder;
	probabilitySquareD = gameSquareCounter[uncommon] * 100 / dieRollsAdder;
	//Find mean value
	meanDieRolls = dieRollsAdder / repetitions;
}

int main(){	
	//Add snakes and ladders to gameBoard array
	initGameBoard();
	//Initilise Seed
	time_t t;
	srand((unsigned)time(&t));

	//Play Game 1000000 time
	for (int k = 0; k < repetitions; k++){
		//Play Game
		playGame();
		//Check if new minRolls exists
	};

	stats();

	return 0;
};