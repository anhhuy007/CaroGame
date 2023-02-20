#include "Control.h"
#include "View.h"
#include "Model.h"
#include <iostream>

void startNewGame() {
	resetGame();
	fixConsoleWindow();
	drawBoard();

	int** board = new int* [_SIZE];
	for (int i = 0; i < _SIZE; i++) {
		board[i] = new int[_SIZE];
	}


	for (int i = 0; i < _SIZE; i++) {
		for (int j = 0; j < _SIZE; j++) {
			board[i][j] = 0;
		}
	}

	bool isFirstPlayerTurn = true;

	while (1) {
		playGame(isFirstPlayerTurn, board);
		playGame(!isFirstPlayerTurn, board);
	}
}

void resetGame() {
	system("cls");
}
