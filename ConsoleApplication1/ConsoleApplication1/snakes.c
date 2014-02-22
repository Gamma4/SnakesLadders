#include <stdio.h>
#include <time.h>

int boardSize = 10;
int Repetitions = 10000;
int position = -1;
int newPosition = 0;
int gameBoard[16] = { 0, 0, 0, 6, 0, 0, 1, 0, -9, 0, 0, 0, 0, 0, 0, 0 };
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

int main(){		
	
	time_t t;
	srand((unsigned)time(&t));

	while (k <= 100000){

		int dieRolls = 0;
		int path[1000] = { 0 };


		while (position <= 10 && dieRolls < 10000){
			//While position = n-6
			while (position <= 5 && dieRolls < 10000){
				newPosition = position + rollDie();
				position = newPosition + gameBoard[position];
				gameSquareCounter[newPosition]++;
				dieRolls++;
			}
			//Ensure the user never goes over 100
			newPosition = position + rollDie();
			if (newPosition > 10){
				newPosition = position;
			}
			else {
				position = newPosition + gameBoard[position];
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