#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Menu.h"

int** board; bool escPressed = false;

void Control::startGame() {
	int option = 0;

	while (option != 6) {
		system("cls");
		option = Menu::MenuScreen(65, 10, 5);

		switch (option) {
		// Game screen
		case 1:
			newGame();
			break;
		}
	}

	system("cls");
	return;
}

void Control::newGame() {
	resetGame();
	View::fixConsoleWindow();
	View::drawBoard();
	View::drawOtherDetail();

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
		Model::playGame(player, board);
		if (Model::checkResult(player == 1 ? 2 : 1, board) != 0) {
			break;
		}
	}

	for (int i = 0; i < _SIZE; i++) {
		delete[] board[i];
	}
	delete[] board;
}

void Control::resetGame() {
	PlaySound(NULL, NULL, 0);
	system("cls");
}

void Control::exitGame() {
	escPressed = true;
	system("cls");
}
