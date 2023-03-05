#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Menu.h"

int** board; bool escPressed = false;

void Control::startGame() {
	// initialize default configuration
	system("color f0");
	View::fixConsoleWindow();

	// start menu screen
	MenuOption option = MenuScreen();

	switch (option) {
	case MenuOption::CONTINUE:
		//Control::continueGame();
		break;
	case MenuOption::NEW_GAME_VS_PLAYER:
		Control::newGame();
		break;
	case MenuOption::NEW_GAME_VS_COMPUTER_EASY:
		//Control::newGame();
		break;
	case MenuOption::NEW_GAME_VS_COMPUTER_HARD:
		//Control::newGame();
		break;
	case MenuOption::LOAD_GAME:
		//Control::loadGame();
		break;
	case MenuOption::SETTING:
		//Control::setting();
		break;
	case MenuOption::ABOUT:
		//Control::about();
		break;
	case MenuOption::QUIT:
		Control::quitGame();
		break;
	}
}

void Control::newGame() {
	Control::resetGame();
	View::drawBoard();
	View::drawOtherDetail();

	// create board
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

void Control::quitGame() {
	escPressed = true;
	system("cls");
}
