#pragma once
#include <iostream>
#include "Model.h"

namespace Control {
	void playWithHuman(Model::GameInformation game_info);	
	void playWithComputer(Model::GameInformation game_info);
	void quitGame();
	void startGame();
	void returnMenu();
	void resetGame();
	void saveGame(Model::GameInformation& game_info);
	void loadGame();
	Model::GameInformation initNewGame(Model::GameMode mode);
	void NavigationController();
}

