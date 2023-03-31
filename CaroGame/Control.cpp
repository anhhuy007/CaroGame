#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Menu.h"
#include "FileIO.h"
#include <string>
#include "InputHandle.h"
#include <thread>

bool escPressed = false;
bool isPauseGame = true;

void Control::startGame() {
	// initialize default configuration
	system("color f0");
	View::fixConsoleWindow();
	View::textStyle(22);

	// show splash screen
	/*View::splashScreen();
	system("cls");*/

	// show menu screen
	Control::NavigationController();
}

void Control::NavigationController() {
	// start menu screen
	View::drawCaroGameText(0);
	MenuOption option = MenuScreen();
	
	switch (option) {
		
	case MenuOption::NEW_GAME_VS_PLAYER:
		Control::newGame(1, 1, initNewGame());
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
		instructionMenu();
		Control::returnMenu();
		break;
		
	case MenuOption::SETTING:
		settingMenu();
		Control::returnMenu();
		break;
		
	case MenuOption::ABOUT:
		aboutMenu();
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

Model::GameInformation Control::initNewGame() {
	Model::GameInformation game_info;

	// input user name
	string p1 = InputHandle::getPlayerName("Enter Player 1 name: ", "");
	strcpy(game_info.player1.name, p1.c_str());

	string p2 = InputHandle::getPlayerName("Enter Player 2 name: ", p1);
	strcpy(game_info.player2.name, p2.c_str());

	system("cls");
	cout << "Player 1: " << game_info.player1.name << endl;
	cout << "Player 2: " << game_info.player2.name << endl;
	system("pause");

	// init game information
	game_info.isFirstPlayerTurn = true;
	game_info.timeRemained = 1200;
	game_info.board = Model::Board();
	memset(game_info.playerMoveHistory, 0, sizeof(game_info.playerMoveHistory));
	game_info.moveHistorySize = 0;
	game_info.curX = 0;
	game_info.curY = 0;
	game_info.endGame = false;

	return game_info;
}

void Control::newGame(bool vsHuman, bool isEasy, Model::GameInformation game_info) {
	Control::resetGame();
	// draw game board and game information
	View::drawGameBoard();
	Model::drawXO(game_info.board);
	
	View::drawGamePlayInfoBox({ 75,13 }, 64, 15, View::Color::BLACK);
	escPressed = false;
	string player1_name = game_info.player1.name;
	wstring name1(player1_name.begin(), player1_name.end());
	View::drawBorder3(75, 75 + 20, 0, 0 + 10, name1);
	string player2_name = game_info.player2.name;
	wstring name2(player2_name.begin(), player2_name.end());
	View::drawBorder3( 119, 119 + 20, 0, 0 + 10,name2);
	View::drawIronmanAvatar(69,-2);
	//View::drawBotAvatar(113,-2);
	//View::drawSpidermanAvatar(113,-2);
	View::drawThanosAvatar(113, -2);
	View::drawVSText();
	escPressed = false;

	View::drawBorder2(80, 80 + 55, 31, 30 + 4);
	View::drawF1F2list(88,32);
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
			View::drawWinner(1, 1, name1, name2);
			
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
	Control::NavigationController();
}
// save game to file
void Control::saveGame(Model::GameInformation& game_info) {
	char* file; std::string fileName;
	
	if (strlen(game_info.name) == 0) {
		// input file name from keyboard
		fileName = InputHandle::getFileName(false, View::WINDOW_SIZE);

		// check if player want to return
		if (fileName == "-1") {
			return;
		}

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
		View::printCenteredToast(L"Save game successfully!", View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
		FileIO::saveFileNameToFile(fileName);
	}
	else {
		View::printCenteredToast(L"Save game failed!", View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
	}
	system("pause");
	system("cls");
}

// load game from file
void Control::loadGame() {
	// show saved game list
	
	View::drawSavedGameTable(FileIO::getSavedGameList(), { 20, 15, 50, 30 });
	std::string fileName = InputHandle::getFileName(true, { 70, 15, 100, 20 });

	// check if player want to return menu
	if (fileName == "-1") {
		Control::returnMenu();
		return;
	}

	std::string filePath = FileIO::folder + fileName + FileIO::extension;
	
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
	}
}


