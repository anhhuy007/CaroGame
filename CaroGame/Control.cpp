#include "Control.h"

int** board; bool escPressed = false;

void startGame() {
	int option = 0;

	while (option != 6) {
		system("cls");
		option = MenuScreen(65, 10, 5);

		switch (option) {
		case 1:
			newGame();
			break;
		}
	}

	system("cls");
	return;
}

void newGame() {
	resetGame();
	fixConsoleWindow();
	drawBoard();
	drawOtherDetail();

	board = new int* [_SIZE];
	for (int i = 0; i < _SIZE; i++) {
		board[i] = new int[_SIZE];
	}

	for (int i = 0; i < _SIZE; i++) {
		for (int j = 0; j < _SIZE; j++) {
			board[i][j] = 0;
		}
	}

	int player = 1;  escPressed = false;

	while (!escPressed) {
		playGame(player, board);
		if (checkResult(player == 1 ? 2 : 1, board) != 0) {
			break;
		}
	}

	for (int i = 0; i < _SIZE; i++) {
		delete[] board[i];
	}
	delete[] board;
}

void resetGame() {
	PlaySound(NULL, NULL, 0);
	system("cls");
}

void exitGame() {
	escPressed = true;
	system("cls");
}
