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
	memset(game_info.board, 0, sizeof(game_info.board));
	return game_info;
}

void Control::startGame() {
	// initialize default configuration
	system("color f0");
	View::fixConsoleWindow();
	View::textStyle();

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
	escPressed = false;

	while (!game_info.endGame && !escPressed) {
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

		if (escPressed) break;

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
	Control::startMenuScreen();
}

bool Control::isValidFileName(std::string file) {
	for (int i = 0; i < file.length(); i++) {
		// check if file contain only alphabet and number
		if (!isalpha(file[i]) && !isdigit(file[i])) return false;
 	}

	return true;
}

bool Control::fileNameExisted(std::string file) {
	file += ".dat";
	// check if file is already exist
	std::ifstream ifs(file);
	if (ifs.good()) return true;

	return false;
}

// save game to file
void Control::saveGame(Model::GameInformation& game_info) {
	char* file;
	std::string fileName = "";
	if (strlen(game_info.name) == 0) {
		while (1) {
			system("cls");
			// input new file name
			wstring wstr = L"Enter file name: ";
			wstring note = L"(Note: File name must contain only alphabet and number)";
			COORD spot = View::getCenteredSpot(note, View::WINDOW_SIZE);
			View::gotoXY(spot.X, spot.Y + 1);
			wcout << note;
			View::gotoXY(spot.X, spot.Y);
			wcout << wstr;
			cin >> fileName;

			// check if file name is valid
			if (!Control::isValidFileName(fileName)) {
				wstr = L"Invalid file name! Please try again.";
				View::printCenteredToast(wstr, View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
				Sleep(1000);
			}
			else if (Control::fileNameExisted(fileName)) {
				wstr = L"File name already existed! Please try again.";
				View::printCenteredToast(wstr, View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
				Sleep(1000);
			}
			else break;
		}

		// save input name to game_info
		strcpy(game_info.name, fileName.c_str());
		
		// save file to GameSaved folder
		fileName = FileIO::folder + fileName + FileIO::extension;
		file = new char[fileName.length() + 1];
		strcpy(file, fileName.c_str());
	}
	else {
		// get filename from game_info
		string fileName = game_info.name;
		fileName = FileIO::folder + fileName + FileIO::extension;
		file = new char[fileName.length() + 1];
		strcpy(file, fileName.c_str());
	}
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
void Control::loadGame(char* name) {
	// read game information from file
	Model::GameInformation game_info = FileIO::readGameInfoFromFile(name);
	// load game
}


