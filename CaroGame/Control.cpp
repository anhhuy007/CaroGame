#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Menu.h"
#include "FileIO.h"
#include <string>

bool escPressed = false;

Model::GameInformation Control::initNewGame() {
	Model::GameInformation game_info;
	
	// init game information
	game_info.player1 = { "Player 1", 0, 1 };
	game_info.player2 = { "Player 2", 0, 0 };
	game_info.isFirstPlayerTurn = true;
	game_info.timeRemained = 1200;
	game_info.curX = 0;
	game_info.curY = 0;
	game_info.endGame = false;
	game_info.board = Model::Board();
	return game_info;
}

void Control::startGame() {
	// initialize default configuration
	system("color f0");
	View::fixConsoleWindow();
	View::textStyle(24);

	// show splash screen
	/*View::splashScreen();
	system("cls");*/

	// show menu screen
	Control::startMenuScreen();
}

void Control::startMenuScreen() {
	// start menu screen
	View::drawCaroGameText(0);
	MenuOption option = MenuScreen();

	switch (option) {
	case MenuOption::CONTINUE:
		//Control::continueGame();
		break;
	case MenuOption::NEW_GAME_VS_PLAYER:
		Control::newGame(true, true, Control::initNewGame());
		break;
	case MenuOption::NEW_GAME_VS_COMPUTER_EASY:
		//Control::newGame();
		break;
	case MenuOption::NEW_GAME_VS_COMPUTER_HARD:
		//Control::newGame();
		break;
	case MenuOption::LOAD_GAME:
		Control::loadGame();
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

void Control::newGame(bool vsHuman, bool isEasy, Model::GameInformation game_info) {
	// draw game board and other details
	Control::resetGame();
	View::drawBoard();
	// draw X and O on the board
	Model::drawXO(game_info.board);
	
	View::drawGamePlayInfoBox({ 75,12 }, 63, 18, View::Color::BLACK);
	escPressed = false;

	while (!game_info.endGame && !escPressed) {
		// player 1 turn
		Model::playerTurn(game_info.player1, game_info);
		Model::GameResult result = Model::checkResult(1, game_info.board.value);
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

		if (escPressed) break;

		// player 2 turn
		Model::playerTurn(game_info.player2, game_info);
		result = Model::checkResult(2, game_info.board.value);
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
	Control::startMenuScreen();
}
// save game to file
void Control::saveGame(Model::GameInformation& game_info) {
	char* file; std::string fileName;
	
	if (strlen(game_info.name) == 0) {
		// input file name from keyboard
		fileName = FileIO::getFileName(false);

		// save input name to game_info
		strcpy(game_info.name, fileName.c_str());
	}
	else {
		// get filename from game_info
		fileName = game_info.name;
	}

	// format file name to path name
	std::string filePath = FileIO::folder + fileName + FileIO::extension;
	file = new char[filePath.length() + 1];
	strcpy(file, filePath.c_str());

	// write game information to file
	bool isSuccess = FileIO::writeGameInfoToFile(file, game_info);

	if (isSuccess) {
		View::printCenteredToast(L"Save game successfully!", View::WINDOW_SIZE, View::Color::BLACK, View::Color::GREEN);
	}
	else {
		View::printCenteredToast(L"Save game failed!", View::WINDOW_SIZE, View::Color::BLACK, View::Color::RED);
	}
	system("pause");
	system("cls");
}

// load game from file
void Control::loadGame() {
	// get file name from keyboard 
	std::string filePath = FileIO::folder + FileIO::getFileName(true) + FileIO::extension;
	char* file = new char[filePath.length() + 1];
	strcpy(file, filePath.c_str());
	
	// read game information from file
	Model::GameInformation game_info = FileIO::readGameInfoFromFile(file);
	if (game_info.name != "") {
		// start game
		Control::newGame(true, true, game_info);
	}
	else {
		View::printCenteredToast(L"Load game failed!", View::WINDOW_SIZE, View::Color::BLACK, View::Color::RED);
		system("pause");
		system("cls");
	}
}


