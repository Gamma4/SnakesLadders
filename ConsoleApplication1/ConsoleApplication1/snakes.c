#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int boardSize = 10;
int Repetitions = 10000;
int position = -1;
int newPosition = 0;
int gameBoard[101] = { 0 };
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
	{ 87, 63 }, 
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
int gameSquareCounter[10] = { 0 };
int dieRollHistory[10] = { 0 };
int minRolls = 1000;
int i = 0;
int k = 0;
int dieRolls[5] = { 0 };

int rollDie(){
	//Roll DICE
	int diceroll;
	/* Intializes random number generator */	
	diceroll = rand() % 6 + 1;
	return diceroll;
};

int initGameBoard(){
	for (i = 0; i < 19; i++){
		gameBoard[snakesLadders[i][0]] = snakesLadders[i][1];
	}
}

int main(){	

	initGameBoard();

	time_t t;
	srand((unsigned)time(&t));

	while (k <= 100000){

		int dieRolls = 0;
		int path[1000] = { 0 };

		while (position <= 10 && dieRolls < 10000){
			//While position = n-6
			while (position <= 5 && dieRolls < 10000){
				position = position + rollDie(1000);
				position = position + gameBoard[position];
				gameSquareCounter[position]++;
				dieRolls++;
			}
			//Ensure the user never goes over 100
			newPosition = position + rollDie();
			if (newPosition > 10){
				newPosition = position;
			}
			else {
				newPosition = newPosition + gameBoard[newPosition];
			}
			gameSquareCounter[newPosition]++;
			dieRolls++;
		}

		if (dieRolls < minRolls){
			minRolls = dieRolls;
		}

		dieRollHistory[k] = dieRolls;

		int common = 0;
		for (i = 0; i <= 10; i++){
			if (gameSquareCounter[i] > common){
				common = gameSquareCounter[i];
			}
		}
	}
};