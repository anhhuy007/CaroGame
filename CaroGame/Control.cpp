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
	case MenuOption::INSTRUCTION:
		aboutMenu({ 65, 10 }, View::Color::BLACK, View::Color::WHITE);
		Control::returnMenu();
		break;
	case MenuOption::SETTING:
		//Control::setting();
		break;
	case MenuOption::ABOUT:
		aboutMenu({ 65, 10 }, View::Color::BLACK, View::Color::WHITE);
		Control::returnMenu();
		break;
	case MenuOption::BACK:
		Control::returnMenu();
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

		Model::GameResult result = Model::checkResult(player == 1 ? 2 : 1, board);
		
		if (result.first != 0) {
			// show winner here
			// ....
			View::gotoXY(0, 0);
			cout << "Player " << result.first << " win!" << endl;
			/*for (int i = 0; i < result.second.size(); i++) {
				cout << result.second[i].X << " " << result.second[i].Y << endl;
			}*/

			system("pause");
			
			quitGame();
			break;
		}
	}

	for (int i = 0; i < _SIZE; i++) {
		delete[] board[i];
	}
	delete[] board;

	Control::returnMenu();
}

void Control::resetGame() {
	PlaySound(NULL, NULL, 0);
	system("cls");
}

void Control::quitGame() {
	escPressed = true;
	system("cls");
}

void Control::returnMenu() {
	// return to menu screen
	system("cls");
	Control::startGame();
}
