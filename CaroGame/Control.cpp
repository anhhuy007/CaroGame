#include "Control.h"
#include "View.h"
#include "Model.h"
#include <iostream>

int** board; bool escPressed = false;

void startNewGame() {
	resetGame();
	fixConsoleWindow();
	drawBoard();

	board = new int* [_SIZE];
	for (int i = 0; i < _SIZE; i++) {
		board[i] = new int[_SIZE];
	}

	for (int i = 0; i < _SIZE; i++) {
		for (int j = 0; j < _SIZE; j++) {
			board[i][j] = 0;
		}
	}

	int player = 1; 

	while (!checkResult(player, board) && !escPressed) {
		playGame(player, board);
	}
}

void resetGame() {
	system("cls");
}

void exitGame() {
	escPressed = true;
	system("cls");
}
