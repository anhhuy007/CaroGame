#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Model.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace Model;

namespace FileIO {
	const std::string folder = "SavedGame//";
	const std::string extension = ".dat";
	const std::string savedGame = "SavedGameList.txt";

	// write and read all game information to file
	bool WriteGameInfoToFile(char fileName[], GameInformation game_info);
	GameInformation ReadGameInfoFromFile(char fileName[]);

	// write game name, date, game mode to file
	void SaveGameGeneralInformation(std::string fileName, Model::GeneralGameInformation information);
	
	// return list of saved game titles
	std::vector<std::string> GetSavedGameList();

	// write and read game setting to file
	bool SaveSetting(std::string fileName, Setting setting);
	Setting ReadSetting(std::string fileName);

	// checking functions
	bool isValidFileName(std::string file);
	bool fileNameExisted(std::string file);
	bool fileNameExistedInList(std::string file);
}	
