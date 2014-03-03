#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Initilisation Variables
int repetitions = 10000000;
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
	{ 16, -10 },
	{ 47, -21 },
	{ 49, -38 },
	{ 56, -3 },
	{ 62, -43 },
	{ 64, -4 },
	{ 87, -63 },
	{ 93, -20 },
	{ 95, -20 },
	{ 98, -20 },
};
//How many times a game square is landed on
int gameSquareCounter[101] = { 0 };
int nminSquareCounter[101] = { 0 };
float probabilitySquareC = 0;
float probabilitySquareD = 0;
int common = 0;
int uncommon = 0;
//How many rolls it takes to finish a game
int rollHistory[1000];
int minRolls = 100;
long float completeDieRolls = 0;
int meanDieRolls = 0;
int popularRolls = 0;
//Nmin Routes
int rollPath[100000];
int minRoutes = 0; 
//Check RNG
int arrayPRNG[7];
int arrayPRNG2[10000];

int rollDie(){
	//Generate a random number from 1 to 6 and return that number
	int diceroll = rand() % 6 + 1;	
	return diceroll;
};

int initGameBoard(){
	//Populate the array gameBoard with the numerical value of the snakes and ladders
	//[i][0] holds the square the snake/ladder is on
	//[i][1] holds the value of that snake / ladder
	for (int i = 0; i < 19; i++){
		gameBoard[snakesLadders[i][0]] = snakesLadders[i][1];
	}
}

int playGame() {
	//Variables for the game
	int position = 0, i = 0, newPosition = 0, dieRolls = 0, tempRollPath[100];

	//Game loop for squares 1 - 100
	while (position < 100){
		newPosition = position + rollDie();

		//Extra if statement to ensure
		//the user never goes over 100
		if (newPosition <= 100){
			position = newPosition + gameBoard[newPosition];
			gameSquareCounter[position]++;
			
			if (dieRolls <= minRolls){
				tempRollPath[dieRolls] = position;
			};
		};

		dieRolls++;

		//Game loop for squares 1 - 94
		while (position <= 94){
			//Add a die rolls to the current position
			position = position + rollDie();
			//Add the value of any snake / ladder on the new square
			position = position + gameBoard[position];
			//Increment the number of times the user has landed on their square
			gameSquareCounter[position]++;
			//If this is a possible path for Nmin add the position to the temp array
			if (dieRolls <= minRolls){
				tempRollPath[dieRolls] = position;
			};
			//Increment the number of dice rolls for this game
			dieRolls++;
		};
	};

	//Keep a count of the total number of dice rolls for all games
	completeDieRolls = completeDieRolls + dieRolls;
	//Remember how many dice rolls this game took
	rollHistory[dieRolls]++;

	//Check if this is a new min path, or a new path for Nmin exists
	if (dieRolls < minRolls){
		//Reset the counter for min paths
		minRoutes = 0;
		//Set the new minRolls
		minRolls = dieRolls;
		//Clear the path array and make every element 0
		for (i = 0; i < 1000; i++){
			if (rollPath[i] == 0){
				//If the slot is zero then this is the end of the recorded paths and 
				//the rest of the array will also be zero, so you can exit the loop
				i = 1000;
			} else {
				rollPath[i] = 0;
			};
		};
	} else if (dieRolls == minRolls){

		int diff = 0, j = 0, uniqueRoute = 1;

		//Check the current path history to see if this path is already counted for
		//Incrememnt by i + minRolls every time as the array is in blocks which are minRolls in length
		for (i = 0; i <= (minRoutes * minRolls); i = i + minRolls){
			j = 0;
			//Exit the loop if the slot in the rollPath array is zero as this is the end of recorded paths
			//Exit the loop if uniqueRoute == 0 as the path has been found to not be unique
			if (rollPath[i] == 0 || uniqueRoute == 0){
				diff = i;
				i = (minRoutes * minRolls) + 1;
			} else {
				//Compare the temp array against a path in the rollPath Array
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
		//If a unique route exists add it to the rollPath array
		if (uniqueRoute == 1){
			minRoutes++;
			for (i = 0; i < minRolls; i++){
				rollPath[i + diff] = tempRollPath[i];
			};
		};
	};
}

int stats(){
	int i = 0;
	//Find most popular and least Square
	for (i = 0; i <= 100; i++){
		if (gameSquareCounter[i] > gameSquareCounter[common]){
			common = i;
		};
		if ((gameSquareCounter[i] < gameSquareCounter[uncommon] || gameSquareCounter[uncommon] == 0) && gameSquareCounter[i] != 0){
			uncommon = i;
		}
	};
	//Find the most popular rolls to finish a game
	for (i = 0; i < 1000; i++){
		if (rollHistory[i] > rollHistory[popularRolls]){
			popularRolls = i;
		}
	};
	//Adds to the nminSquareCounter array to find out how many times different squares
	//were landed on to complete the game in Nmin rolls
	for (i = 0; i < 3000; i++){
		nminSquareCounter[rollPath[i]]++;
	};
	//Find the probability of landing on most or least popular square
	probabilitySquareC = gameSquareCounter[common] * 100 / completeDieRolls;
	probabilitySquareD = gameSquareCounter[uncommon] * 100 / completeDieRolls;
	//Find the mean number of rolls
	meanDieRolls = completeDieRolls / repetitions;
}

int print(){
	int i = 0;
	//Print the results to a file so they can be imported into excel to transform
	//the data into a visual form

	//Write the number of times each square was landed on
	FILE*fp2;
	fp2 = fopen("squareCounter.txt", "w");
	for (i = 1; i < 101 + 7; i++){
		fprintf(fp2, "%i", gameSquareCounter[i]);
		fprintf(fp2, "\n");
	};
	fclose(fp2);
	//Write how many rolls it took to finish each game
	FILE*fp3;
	fp3 = fopen("rollHistory.txt", "w");
	for (i = 0; i < 1000; i++){
		fprintf(fp3, "%i", rollHistory[i]);
		fprintf(fp3, "\n");
	};
	fclose(fp3);
	//write te number of times eac square was landed on, only for Nmin routes
	FILE*fp4;
	fp4 = fopen("nminPaths.txt", "w");
	for (i = 1; i < 101; i++){
		fprintf(fp4, "%i", nminSquareCounter[i]);
		fprintf(fp4, "\n");
	};
	fclose(fp4);
}

int checkPRNG(){
	for (int i = 0; i < 1000000; i++){
		arrayPRNG[rollDie()]++;
	}
	int i = 0;
	while (i < 1000){
		arrayPRNG2[i]++;
		if (rollDie() == rollDie() && rollDie() == rollDie() && rollDie() == rollDie()){
			i++;
		}
	}
}

int main(){	
	//Add snakes and ladders to gameBoard array
	initGameBoard();
	//Initilise Seed
	time_t t;
	srand((unsigned)time(&t));

	//Play Game 1000000 time
	for (int k = 0; k < repetitions; k++){
		playGame();
	};
	//Generate statistics for the game
	stats();
	//Print results to file
	checkPRNG();
	print();

	return 0;
};