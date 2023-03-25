#pragma once
#include <iostream>
#include "Model.h"

namespace Control {
	void resetGame();
	void newGame(bool vsHuman, bool isEasy);
	void quitGame();
	void startGame();
	void returnMenu();
	void saveGame(Model::GameInformation& game_info);
	void loadGame(char* name);
	Model::GameInformation initNewGame();
	void startMenuScreen();
	bool isValidFileName(std::string file);
	bool fileNameExisted(std::string file);
}

