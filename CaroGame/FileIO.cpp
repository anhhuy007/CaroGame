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

bool FileIO::saveSetting(std::string fileName, Setting setting)
{
	fileName = folder + fileName + extension;
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
	fileName = folder + fileName + extension;
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

