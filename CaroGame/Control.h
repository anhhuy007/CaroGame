#pragma once
#include <iostream>
#include "Model.h"

namespace Control {
	void PlayWithHuman(Model::GameInformation game_info);	
	void PlayWithComputer(Model::GameInformation game_info);
	void QuitGame();
	void StartGame();
	void ReturnMenu();
	void SaveGame(Model::GameInformation& game_info);
	void LoadGame();
	Model::GameInformation initNewGame(Model::GameMode mode);
	void NavigationController();
}

