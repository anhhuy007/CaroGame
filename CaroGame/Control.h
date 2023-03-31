#pragma once
#include <iostream>
#include "Model.h"

namespace Control {
	void newGame(bool vsHuman, bool isEasy, Model::GameInformation game_info);
	void playWithHuman();
	void quitGame();
	void startGame();
	void returnMenu();
	void resetGame();
	void saveGame(Model::GameInformation& game_info);
	void loadGame();
	Model::GameInformation initNewGame();
	void NavigationController();
}

