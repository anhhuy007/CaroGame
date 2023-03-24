#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Menu.h"
#include "FileIO.h"

bool escPressed = false;

Model::GameInformation Control::initNewGame() {
	Model::GameInformation game_info;
	game_info.player1.isFirstPlayer = true;
	game_info.isFirstPlayerTurn = true;
	game_info.timeRemained = 1200;
	game_info.curX = 0;
	game_info.curY = 0;
	game_info.endGame = false;
	memset(game_info.board, 0, sizeof(game_info.board));
	return game_info;
}

void Control::startGame() {
	// initialize default configuration
	system("color f0");
	View::fixConsoleWindow();
	View::textStyle();

	// start menu screen
	MenuOption option = MenuScreen();

	switch (option) {
	case MenuOption::CONTINUE:
		//Control::continueGame();
		break;
	case MenuOption::NEW_GAME_VS_PLAYER:
		Control::newGame(true, true);
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
		instructionMenu({ 60, 2 }, View::Color::BLACK, View::Color::WHITE);
		Control::returnMenu();
		break;
	case MenuOption::SETTING:
		settingMenu({ 60, 10 }, View::Color::BLACK, View::Color::PURPLE);
		Control::returnMenu();
		break;
	case MenuOption::ABOUT:
		aboutMenu({ 65, 2 }, View::Color::BLACK, View::Color::WHITE);
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

void Control::newGame(bool vsHuman, bool isEasy) {
	Control::resetGame();
	View::drawBoard();
	View::drawOtherDetail(); 
	Model::GameInformation game_info = Control::initNewGame();

	while (!game_info.endGame) {
		Model::playerTurn(game_info.player1, game_info);
		Model::GameResult result = Model::checkResult(1, game_info.board);
		// check if player 1 win
		if (result.first != 0) {
			// show winner here
			// ....
			View::gotoXY(0, 0);
			cout << "Player " << result.first << " win!" << endl;

			// show winning moves
			View::showWinningMoves(result.first, result.second);

			// show winner congratulation screen

			game_info.endGame = true;
			break;
		}

		Model::playerTurn(game_info.player2, game_info);
		result = Model::checkResult(2, game_info.board);
		// check if player 2 win
		if (result.first != 0) {
			// show winner here
			// ....
			View::gotoXY(0, 0);
			cout << "Player " << result.first << " win!" << endl;

			// show winning moves
			View::showWinningMoves(result.first, result.second);

			// show winner congratulation screen

			game_info.endGame = true;
			break;
		}
	}
	
	system("pause");
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

// save game to file
void Control::saveGame(Model::GameInformation game_info) {
	// create file name
	char fileName[50];
	strcpy(fileName, game_info.name);
	// write game information to file
	FileIO::writeGameInfoToFile(fileName, game_info);
}

// load game from file
void Control::loadGame(char* name) {
	// read game information from file
	Model::GameInformation game_info = FileIO::readGameInfoFromFile(name);
	// load game
}


