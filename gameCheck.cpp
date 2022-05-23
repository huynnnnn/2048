#include "gameCheck.h"

//kiểm tra có 2048
bool checkWin(int **&tab, int size) {
	bool win = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tab[i][j] == 2048) win = 1;
		}
	}

	return win;
}

//ktra ô trống
bool checkPut(int **&tab, int size) {
	bool put = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tab[i][j] == 0) put = 1;
		}
	}

	return put;
}
bool checkLose(int **&tab, int size) {
	bool lose = 1;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (tab[i][j] == tab[i][j + 1]) lose = 0;
		}
	}
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size; j++) {
			if (tab[i][j] == tab[i + 1][j]) lose = 0;
		}
	}

	if (checkPut(tab, size)) lose = 0;

	return lose;
}
bool checkToRandom(int **&tab, int **&backTab, int size) {
	int can_put = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (tab[i][j] != backTab[i][j]) can_put = 1;
		}
	}
	return can_put;
}