#include "Board.h"

//create array
int** createtab(int size) {
	int **tab;
	tab = new int *[size];
	for (int i = 0; i < size; ++i) tab[i] = new int[size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tab[i][j] = 0;
		}
	}
	int X = rand() % size;
	int Y = rand() % size;
	tab[X][Y] = 2;
	X = rand() % size;
	Y = rand() % size;
	tab[X][Y] = 2;

	return tab;
}

void randomOnBoard(int **&tab, int size) {

	if (checkPut(tab, size)) {
		int values[10] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
		int value = values[rand() % 10];

		int X = rand() % size;
		int Y = rand() % size;
		if (tab[X][Y] == 0) tab[X][Y] = 2;
		else {
			while (tab[X][Y] != 0) {
				X = rand() % size;
				Y = rand() % size;
			}
			tab[X][Y] = value;
		}
	}
}

//copy one array to another
void copyTab(int **&tab1,int **&tab2, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) tab1[i][j] = tab2[i][j];
	}
}