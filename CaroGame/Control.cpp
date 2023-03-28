#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Menu.h"

int** board; bool escPressed = false;

void Control::startGame() {
	// initialize default configuration
	system("color f0");
	View::fixConsoleWindow();
	View::textStyle();
	View::drawCaroGameText();
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
	//View::drawBoard();
	View::drawBoard2(16,16);
	//View::drawBorder2(67, 67 + 45, 19, 19 + 10);
	//View::drawOtherDetail();
	//View::drawTurnBoard();
	//View::drawTrophy();
	
	View::drawBorder3(71, 71 + 20, 2, 2 + 10);
	//View::drawIronmanAvatar();

	View::drawBorder3(110, 110 + 20, 2, 2 + 10);
	//View::drawBotAvatar();

	View::drawVSText();
	View::drawSpidermanAvatar();
	View::drawThanosAvatar();

	// create board
	board = new int* [View::_SIZE];
	for (int i = 0; i < View::_SIZE; i++) {
		board[i] = new int[View::_SIZE];
	}

	for (int i = 0; i < View::_SIZE; i++) {
		for (int j = 0; j < View::_SIZE; j++) {
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
			
			// show winning moves
			View::showWinningMoves(result.first, result.second);

			// show winner congratulation screen
				
			
			system("pause");
			quitGame();
			break;
		}
	}

	for (int i = 0; i < View::_SIZE; i++) {
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
