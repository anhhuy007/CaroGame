#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Model.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace Model;

namespace FileIO {
	const string folder = "SavedGame//";
	const string extension = ".dat";

	bool writeGameInfoToFile(char fileName[], GameInformation game_info);
	GameInformation readGameInfoFromFile(char fileName[]);
	bool isValidFileName(std::string file);
	bool fileNameExisted(std::string file);
}	
