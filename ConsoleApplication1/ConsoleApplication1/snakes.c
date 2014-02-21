#include <stdio.h>
#include <time.h>

int boardSize = 10;
int Repetitions = 10000;
int position = 0;
int gameBoard[10] = { 0, 0, 0, 6, 0, 0, 1, 0, -9, 0 };
int gameSquareCounter[10] = { 0 };
int dieRollHistory[10] = { 0 };
int minRolls = 1000;
int i = 0;
int k = 0;

int dieRolls[5] = { 0 };

int rollDie(){
	//Roll DICE
	int diceroll;
	time_t t;


	/* Intializes random number generator */
	srand((unsigned)time(&t));
	diceroll = rand() % 6 + 1;
	return diceroll;
};

int main(){
	while (k <= 100000){
		int dieRolls = 0;
		int path[1000] = { 0 };

		while (position <= 10 && dieRolls < 10000){
			position = position + rollDie();
			position = position + gameBoard[position];
			gameSquareCounter[position]++;
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