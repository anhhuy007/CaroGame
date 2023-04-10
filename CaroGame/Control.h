#pragma once
#include <iostream>
#include "Model.h"

namespace Control {
	void NavigationController();
	void StartGame();
	void ReturnMenu();
	void QuitGame();
	void ResetGame(Model::GameInformation& game_info);
	Model::GameInformation InitNewGame(Model::GameMode mode);
	void PlayWithHuman(Model::GameInformation game_info);
	void PlayWithComputer(Model::GameInformation game_info);
	void SaveGame(Model::GameInformation& game_info);
	void LoadGame();
}

