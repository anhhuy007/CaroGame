#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Model.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <direct.h>
using namespace Model;

namespace FileIO {
	const string folder = "SavedGame//";
	const string extension = ".dat";
	const string savedGame = "SavedGameList.txt";

	bool writeGameInfoToFile(char fileName[], GameInformation game_info);
	void saveFileNameToFile(std::string fileName);
	GameInformation readGameInfoFromFile(char fileName[]);
	bool isValidFileName(std::string file);
	bool fileNameExisted(std::string file);
	bool fileNameExistedInList(std::string file);
	bool saveSetting(std::string fileName, Setting setting);
	Setting readSetting(std::string fileName);
	std::vector<std::string> getSavedGameList();
}	
