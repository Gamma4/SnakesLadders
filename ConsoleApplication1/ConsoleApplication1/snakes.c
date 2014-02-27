#include <stdio.h>
#include <time.h>

int repetitions = 1000000;
int boardLength = 101;
int position = 0;
int newPosition = 0;
int tempRollHistory[1000];
int rollHistory[1000];
int gameBoard[101] = { 0 };
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
	{ 47, -26 },
	{ 49, -38 },
	{ 56, -3 },
	{ 62, -43 },
	{ 64, -4 },
	{ 93, -20 },
	{ 95, -20 },
	{ 98, -20 },
};
int minRolls = 0;
int i = 0;
int k = 0;
int common = 0;
int uncommon = 0;
int dieRolls = 0;
int dieRollsAdder = 0;
int meanDieRolls = 0;
int r = 0;
int dieRollHistory[6] = { 0 };
int probabilitySquareC = 0;
int probabilitySquareD = 0;

int rollDie(){
	//Roll DICE
	int diceroll;
	/* Intializes random number generator */	
	diceroll = rand() % 6 + 1;
	dieRollHistory[diceroll - 1]++;
	return diceroll;
};

int initGameBoard(){
	for (i = 0; i < 19; i++){
		gameBoard[snakesLadders[i][0]] = snakesLadders[i][1];
	}
}

int playGame() {
	//The game
	while (position < 100 && dieRolls < 10000){
		//While position = n-6
		while (position <= 94 && dieRolls < 10000){
			position = position + rollDie();
			position = position + gameBoard[position];
			gameSquareCounter[position]++;
			if (r <= minRolls){
				tempRollHistory[r] = newPosition;
			};
			dieRolls++;
			dieRollsAdder++;
			r++;
		};
		newPosition = position + rollDie();

		//Ensure the user never goes over 100
		if (newPosition <= 100){
			position = newPosition + gameBoard[newPosition];
			gameSquareCounter[position]++;
		};

		if (r <= minRolls){
			rollHistory[r] = position;
		};
		dieRolls++;
		dieRollsAdder++;
	};
}

int main(){	
	//Add snakes and ladders to gameBoard awway
	initGameBoard();
	//Initilise Seed
	time_t t;
	srand((unsigned)time(&t));

	//Play Game 1000000 time
	while (k < repetitions){
		//reset game variables
		dieRolls = 0;
		r = 0;
		position = 0;
		//Play Game
		playGame();
		//Check if new minRolls exists
		if (dieRolls < minRolls || minRolls == 0){
			minRolls = dieRolls;
		};
		//Increment turn counter
		k++;
	};

	//Find most popular Square
	for (i = 0; i <= 100; i++){
		if (gameSquareCounter[i] > gameSquareCounter[common]){
			common = i;
		};
		if (gameSquareCounter[i] < gameSquareCounter[uncommon] && gameSquareCounter[i] != 0 || gameSquareCounter[uncommon] == 0){
			uncommon = i;
		}
	};

	probabilitySquareC = gameSquareCounter[common] * 100 / dieRollsAdder;
	probabilitySquareD = gameSquareCounter[uncommon] * 100 / dieRollsAdder;
	//Find mean value
	meanDieRolls = dieRollsAdder / repetitions;

	return 0;
};