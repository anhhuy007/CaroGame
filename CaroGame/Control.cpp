#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Control.h"
#include "View.h"
#include "Menu.h"
#include "FileIO.h"
#include "InputHandle.h"
#include <string>

bool escPressed = false;

void Control::StartGame() {
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

// control navigation between menu and game
void Control::NavigationController() {
	// start menu screen
	View::drawCaroGameText(0);
	MenuOption option = MenuScreen();
	
	switch (option) {

	case MenuOption::NEW_GAME_VS_PLAYER:
		Control::PlayWithHuman(initNewGame({ Model::PLAY_WITH_HUMAN, Model::EASY }));
		break;
		
	case MenuOption::NEW_GAME_VS_COMPUTER_EASY:
		Control::PlayWithComputer(initNewGame({ Model::PLAY_WITH_COMPUTER, Model::EASY }));
		break;
		
	case MenuOption::NEW_GAME_VS_COMPUTER_HARD:
		Control::PlayWithComputer(initNewGame({ Model::PLAY_WITH_COMPUTER, Model::HARD }));
		break;
		
	case MenuOption::LOAD_GAME:
		Control::LoadGame();
		break;
		
	case MenuOption::INSTRUCTION:
		InstructionMenu();
		Control::ReturnMenu();
		break;
		
	case MenuOption::SETTING:
		SettingMenu();
		Control::ReturnMenu();
		break;
		
	case MenuOption::ABOUT:
		AboutMenu();
		Control::ReturnMenu();
		break;
		
	case MenuOption::BACK:
		Control::ReturnMenu();
		break;
		
	case MenuOption::QUIT:
		Control::QuitGame();
		break;
	}
}

// initialize information for new game
Model::GameInformation Control::initNewGame(Model::GameMode mode) {
	Model::GameInformation game_info;

	system("cls");
	// if player2 is human
	if (mode.isPlayWithHuman == Model::PLAY_WITH_HUMAN) {
		// input player1 name
		std::string p1 = InputHandle::GetPlayerName("Enter Player 1 name: ", "");
		strcpy(game_info.player1.name, p1.c_str());

		// if exit game
		if (p1 == "-1") {
			Control::ReturnMenu();
			return GameInformation();
		}

		std::string p2 = InputHandle::GetPlayerName("Enter Player 2 name: ", p1);
		strcpy(game_info.player2.name, p2.c_str());

		// if exit game
		if (p2 == "-1") {
			Control::ReturnMenu();
			return GameInformation();
		}
	}
	// if player2 is computer
	else {
		std::string p1 = InputHandle::GetPlayerName("Enter Player name: ", "");
		strcpy(game_info.player1.name, p1.c_str());

		// if exit game
		if (p1 == "-1") {
			Control::ReturnMenu();
			return GameInformation();
		}

		strcpy(game_info.player2.name, "Computer");
	}

	// initialize game information
	game_info.isFirstPlayerTurn = true;
	game_info.gameMode = mode;
	game_info.timer = 0;
	game_info.board = Model::Board();
	memset(game_info.playerMoveHistory, 0, sizeof(game_info.playerMoveHistory));
	game_info.moveHistorySize = 0;
	game_info.curX = View::LEFT + 38;
	game_info.curY = View::TOP + 19;
	game_info.endGame = false;

	return game_info;
}

// play game with human
void Control::PlayWithHuman(Model::GameInformation game_info) {
	Model::updateInform(game_info, { 75, 13 }, 64, 15, View::Color::BLACK);
	std::wstring name1 = game_info.player1.getWStringName();
	std::wstring name2 = game_info.player2.getWStringName();
	escPressed = false;

	// draw game board and game information
	View::DisplayGame(game_info.board.value, game_info.board.gui, name1, name2);
	
	while (!game_info.endGame && !escPressed) {
		Player player = game_info.isFirstPlayerTurn ? game_info.player1 : game_info.player2;
		Model::playerTurn(player, game_info);
		Model::GameResult result = Model::checkResult(game_info.isFirstPlayerTurn ? 2 : 1, game_info.board.value);
		
		// if game is end
		if (result.first != 0) {
			game_info.endGame = true;
			View::displayGameResult(result.first, result.second, name1, name2);
			
			// show dialog check if player want to play again or return menu
			system("cls");
			View::confirmDialog(
				L"Do you want to play again? (Your current game will be lost and player score will be updated)",
				{ 15, 10 },
				[&]() -> void {
					// if click YES then return menu
					//Control::ResetGame(game_info);
					Control::PlayWithHuman(game_info);
				},
				[&]() -> void {
					// if click NO then continue game
					// restore screen's information
					Control::ReturnMenu();
				}
				);
		}
		
		if (escPressed) break;
	}

	Control::ReturnMenu();
}

// play game with computer
void Control::PlayWithComputer(Model::GameInformation game_info) {
	Model::updateInform(game_info, { 75, 13 }, 64, 15, View::Color::BLACK);
	std::wstring name1 = game_info.player1.getWStringName();
	std::wstring name2 = game_info.player2.getWStringName();
	escPressed = false;

	// draw game board and game information
	View::DisplayGame(game_info.board.value, game_info.board.gui ,name1, name2);

	while (!game_info.endGame && !escPressed) {
		Player player = game_info.isFirstPlayerTurn ? game_info.player1 : game_info.player2;
		if (strcmp(player.name, "Computer") == 0) Model::computerTurn(player, game_info);
		else Model::playerTurn(player, game_info);
		
		std::pair<int, std::vector<COORD>> result = Model::checkResult(game_info.isFirstPlayerTurn ? 2 : 1, game_info.board.value);
		if (result.first != 0) {
			game_info.endGame = true;
			View::displayGameResult(result.first, result.second, name1, name2);
			
			// show dialog check if player want to play again or return menu
			system("cls");
			View::confirmDialog(
				L"Do you want to play again? (Your current game will be lost and player score will be updated)",
				{ 15, 10 },
				[&]() -> void {
					// if click YES then return menu
					//Control::ResetGame(game_info);
					Control::PlayWithComputer(game_info);
				},
				[&]() -> void {
					// if click NO then continue game
					// restore screen's information
					Control::ReturnMenu();
				}
				);
		}
	}
	
	Control::ReturnMenu();
}

void Control::QuitGame() {
	escPressed = true;
	system("cls");
}

void Control::ReturnMenu() {
	// return to menu screen
	system("cls");
	Control::NavigationController();
}
// save game to file
void Control::SaveGame(Model::GameInformation& game_info) {
	char* file; std::string fileName;
	
	if (strlen(game_info.name) == 0) {
		// input file name from keyboard
		fileName = InputHandle::GetFileName(false, View::WINDOW_SIZE);

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
	bool isSuccess = FileIO::WriteGameInfoToFile(file, game_info);

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
}

// load game from file
void Control::LoadGame() {
	system("cls");

	// print LOAD GAME title text
	View::drawLoadGameText();

	// show saved game list and return game name 
	std::string fileName = GetSavedGameTitle(FileIO::GetSavedGameList(), { 45, 15, 95, 30 });

	// check if player want to return menu
	if (fileName == "-1") {
		Control::ReturnMenu();
		return;
	}

	// format file name to path name
	std::string filePath = FileIO::folder + fileName + FileIO::extension;
	char* file = new char[filePath.length() + 1];
	strcpy(file, filePath.c_str());
	
	// read game information from file
	Model::GameInformation game_info = FileIO::ReadGameInfoFromFile(file);
	if (game_info.name != "") {
		system("cls");
		if (game_info.gameMode.isPlayWithHuman == Model::PLAY_WITH_HUMAN) {
			// two players game
			Control::PlayWithHuman(game_info);
		}
		else {
			// play with computer
			Control::PlayWithComputer(game_info);
		}
	}
	else {
		View::printCenteredToast(L"Load game failed!", View::WINDOW_SIZE, View::Color::BLACK, View::Color::RED);
		View::pressAnyKey(View::WINDOW_SIZE);
	}
}


