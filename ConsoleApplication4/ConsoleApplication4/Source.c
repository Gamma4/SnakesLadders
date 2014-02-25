#include <stdio.h>

int i = 101;
int j = 101;
int P[101][101] = { 0 };
int f = 6;  //number of sides of the dice

int TransitionMatrix(){

	for (j = 0; j < (100 - f); j++){
		for (i = 1; i <= f; i++){
			P[j][j + i] = 1 / f;            // needs to be changed to improve accuracy since 1/6 is a fucked up numeber
		}
	}

	for (j = 101 - f; j <= (100 - f); j++){
		P[j][j] = (f - 100 + j) / f;
		for (i = 1; i <= (100 - j); i++){
			P[j][j + i] = 1 / f;
		}
	}


	for (i = 0; i <= 101; i++){
		for (j = 0; j <= 101; j++){
			printf("%d", P[j][i]);
		}
		printf("/n");
	}
	return 0;
}