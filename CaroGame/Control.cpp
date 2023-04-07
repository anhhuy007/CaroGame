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
		Control::playWithHuman(initNewGame({ Model::PLAY_WITH_HUMAN, Model::EASY }));
		break;
		
	case MenuOption::NEW_GAME_VS_COMPUTER_EASY:
		Control::playWithComputer(initNewGame({ Model::PLAY_WITH_COMPUTER, Model::EASY }));
		break;
		
	case MenuOption::NEW_GAME_VS_COMPUTER_HARD:
		Control::playWithComputer(initNewGame({ Model::PLAY_WITH_COMPUTER, Model::HARD }));
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

Model::GameInformation Control::initNewGame(Model::GameMode mode) {
	Model::GameInformation game_info;

	// input user name
	string p1 = InputHandle::getPlayerName("Enter Player 1 name: ", "");
	strcpy(game_info.player1.name, p1.c_str());
	 
	// if exit game
	if (p1 == "-1") {
		Control::returnMenu();
		return GameInformation();
	}

	// if user 2 is human then input player name
	if (mode.isPlayWithHuman == Model::PLAY_WITH_HUMAN) {
		string p2 = InputHandle::getPlayerName("Enter Player 2 name: ", p1);
		strcpy(game_info.player2.name, p2.c_str());

		// if exit game
		if (p2 == "-1") {
			Control::returnMenu();
			return GameInformation();
		}
	}
	// if user 2 is computer
	else {
		strcpy(game_info.player2.name, "Computer");
	}

	// initialize game information
	game_info.isFirstPlayerTurn = true;
	game_info.gameMode = mode;
	game_info.timer = 0;
	game_info.board = Model::Board();
	memset(game_info.playerMoveHistory, 0, sizeof(game_info.playerMoveHistory));
	game_info.moveHistorySize = 0;
	game_info.curX = 0;
	game_info.curY = 0;
	game_info.endGame = false;

	return game_info;
}

void Control::playWithHuman(Model::GameInformation game_info) {
	Control::resetGame();
	Model::updateInform(game_info, { 75, 13 }, 64, 15, View::Color::BLACK);
	string player1_name = game_info.player1.name;
	wstring name1(player1_name.begin(), player1_name.end());
	string player2_name = game_info.player2.name;
	wstring name2(player2_name.begin(), player2_name.end());
	escPressed = false;

	// draw game board and game information
	View::drawGameBoard();
	Model::drawXO(game_info.board);
	View::drawGamePlayInfoBox({ 75,13 }, 64, 15, View::Color::BLACK);
	View::drawBorder3(75, 75 + 20, 0, 0 + 10, name1);
	View::drawBorder3(119, 119 + 20, 0, 0 + 10, name2);
	View::drawIronmanAvatar(69, -2);
	View::drawThanosAvatar(113, -2);
	View::drawVSText();
	View::drawBorder2(80, 80 + 55, 31, 30 + 4);
	View::drawF1F2list(88, 32);
	
	while (!game_info.endGame && !escPressed) {
		Player player = game_info.isFirstPlayerTurn ? game_info.player1 : game_info.player2;
		Model::playerTurn(player, game_info);
		Model::GameResult result = Model::checkResult(game_info.isFirstPlayerTurn ? 2 : 1, game_info.board.value);
		if (result.first != 0) {
			game_info.endGame = true;
			View::displayGameResult(result.first, result.second, name1, name2);
			break;
		}
		
		if (escPressed) break;
	}

	Control::returnMenu();
}

void Control::playWithComputer(Model::GameInformation game_info) {
	Control::resetGame();
	Model::updateInform(game_info, { 75, 13 }, 64, 15, View::Color::BLACK);
	string player1_name = game_info.player1.name;
	wstring name1(player1_name.begin(), player1_name.end());
	string player2_name = game_info.player2.name;
	wstring name2(player2_name.begin(), player2_name.end());
	escPressed = false;

	// draw game board and game information
	View::drawGameBoard();
	Model::drawXO(game_info.board);
	View::drawGamePlayInfoBox({ 75,13 }, 64, 15, View::Color::BLACK);
	View::drawBorder3(75, 75 + 20, 0, 0 + 10, name1);
	View::drawBorder3(119, 119 + 20, 0, 0 + 10, name2);
	View::drawIronmanAvatar(69, -2);
	View::drawThanosAvatar(113, -2);
	View::drawVSText();
	View::drawBorder2(80, 80 + 55, 31, 30 + 4);
	View::drawF1F2list(88, 32);

	while (!game_info.endGame && !escPressed) {
		Player player = game_info.isFirstPlayerTurn ? game_info.player1 : game_info.player2;

		View::gotoXY(0, 0);
		cout << "Current player: " << player.name << endl;
		
		if (strcmp(player.name, "Computer") == 0) Model::computerTurn(player, game_info);
		else Model::playerTurn(player, game_info);
		
		pair<int, vector<COORD>> result = Model::checkResult(game_info.isFirstPlayerTurn ? 2 : 1, game_info.board.value);
		if (result.first != 0) {
			game_info.endGame = true;
			View::displayGameResult(result.first, result.second, name1, name2);
			break;
		}
	}
	
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
		View::printCenteredToast(L"Save game successfully!", View::WINDOW_SIZE, View::Color::BLACK, View::Color::GREEN);
		Model::GeneralGameInformation information = Model::GeneralGameInformation(
			game_info.name,
			{0, 0},
			game_info.gameMode
		);
		information.updateNewDate();
		FileIO::SaveGameGeneralInformation(fileName, information);
	}
	else {
		View::printCenteredToast(L"Save game failed!", View::WINDOW_SIZE, View::Color::BLACK, View::Color::RED);
	}
	View::pressAnyKey(View::WINDOW_SIZE);
	system("cls");
}

// load game from file
void Control::loadGame() {
	system("cls");
	View::drawLoadGameText();

	// show saved game list and return game name 
	std::string fileName = GetSavedGameTitle(FileIO::getSavedGameList(), { 45, 15, 95, 30 });

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
		if (game_info.gameMode.isPlayWithHuman == Model::PLAY_WITH_HUMAN) {
			// two players game
			Control::playWithHuman(game_info);
		}
		else {
			// play with computer
			Control::playWithComputer(game_info);
		}
	}
	else {
		View::printCenteredToast(L"Load game failed!", View::WINDOW_SIZE, View::Color::BLACK, View::Color::RED);
		system("pause");
	}
}


