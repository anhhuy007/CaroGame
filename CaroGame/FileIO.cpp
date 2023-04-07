#include "FileIO.h" 

bool FileIO::writeGameInfoToFile(char fileName[], GameInformation game_info) {
	ofstream ofs(fileName, ios::binary);

	if (!ofs) {
		std::cerr << "Cannot open file " << fileName << std::endl;
		return 0;
	}

	ofs.write((char*)&game_info, sizeof(Model::GameInformation));
	ofs.close();
	return 1;
}

// information pattern: name@date@type
void FileIO::SaveGameGeneralInformation(std::string fileName) {
	if (FileIO::fileNameExistedInList(fileName)) return;
	std::ofstream ofs(folder + savedGame, std::ios::app);
	ofs << fileName << std::endl;
	ofs.close();
}

GameInformation FileIO::readGameInfoFromFile(char fileName[]) {
	ifstream ifs(fileName, ios::binary);

	if (!ifs) {
		std::cerr << "Cannot open file " << fileName << std::endl;
		return GameInformation();
	}

	GameInformation game_info;
	ifs.read((char*)&game_info, sizeof(GameInformation));
	ifs.close();
	
	return game_info;
}

bool FileIO::isValidFileName(std::string file) {
	for (int i = 0; i < file.length(); i++) {
		// check if file contain only alphabet and number
		if (!isalpha(file[i]) && !isdigit(file[i])) return false;
	}

	return true;
}

bool FileIO::fileNameExisted(std::string file) {
	file = folder + file + extension;
	// check if file is already exist
	std::ifstream ifs(file);
	if (ifs.good()) return true;

	ifs.close();
	return false;
}

bool FileIO::fileNameExistedInList(std::string file) {
	std::ifstream ifs(folder + savedGame);
	std::string line;
	while (std::getline(ifs, line)) {
		if (line == file) return true;
	}

	ifs.close();
	return false;
}

bool FileIO::saveSetting(std::string fileName, Setting setting)
{
	ofstream ofs(fileName, ios::binary);

	if (!ofs) {
		std::cerr << "Cannot open file " << fileName << std::endl;
		return 0;
	}

	ofs.write((char*)&setting, sizeof(Setting));
	ofs.close();
	return 1;
}

Setting FileIO::readSetting(std::string fileName) {
	ifstream ifs(fileName, ios::binary);

	if (!ifs) {
		std::cerr << "Cannot open file " << fileName << std::endl;
		return Setting();
	}

	Setting setting;
	ifs.read((char*)&setting, sizeof(Setting));
	ifs.close();

	return setting;
}

std::vector<std::string> FileIO::getSavedGameList()	{
	std::vector<std::string> savedGameList;
	ifstream ifs(folder + savedGame);
	
	if (!ifs) {
		std::cerr << "Cannot open file " << folder + savedGame << std::endl;
		return savedGameList;
	}

	std::string line;
	while (getline(ifs, line)) {
		savedGameList.push_back(line);
	}

	ifs.close();
	return savedGameList;
}

