#pragma once
#include <iostream>
#include "Model.h"

namespace Control {
	void resetGame();
	void newGame(bool vsHuman, bool isEasy, Model::GameInformation game_info);
	void quitGame();
	void startGame();
	void returnMenu();
	void saveGame(Model::GameInformation& game_info);
	void loadGame();
	Model::GameInformation initNewGame();
	void startMenuScreen();
}

