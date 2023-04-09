#include "FileIO.h" 

bool FileIO::WriteGameInfoToFile(char fileName[], GameInformation game_info) {
	ofstream ofs(fileName, ios::binary);

	// if cannot open file
	if (!ofs) {
		View::printCenteredToast(L"Cannot open file ", View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
		return 0;
	}

	ofs.write((char*)&game_info, sizeof(Model::GameInformation));
	
	ofs.close();
	return 1;
}

// information pattern: name@date@type
void FileIO::SaveGameGeneralInformation(std::string fileName, Model::GeneralGameInformation information) {
	if (FileIO::fileNameExistedInList(fileName)) return;
	std::ofstream ofs(folder + savedGame, std::ios::app);

	// if cannot open file
	if (!ofs) {
		View::printCenteredToast(L"Cannot open file ", View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
		return;
	}
	
	std::string data = information.getFormatedInformation();
	ofs << data << std::endl;
	ofs.close();
}

GameInformation FileIO::ReadGameInfoFromFile(char fileName[]) {
	ifstream ifs(fileName, ios::binary);

	// if cannot open file
	if (!ifs) {
		View::printCenteredToast(L"Cannot open file ", View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
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
		std::string name = line.substr(0, line.find('@'));
		if (name == file) {
			ifs.close();
			return true;
		}
	}

	ifs.close();
	return false;
}

bool FileIO::SaveSetting(std::string fileName, Setting setting)
{
	ofstream ofs(fileName, ios::binary);

	// if cannot open file
	if (!ofs) {
		View::printCenteredToast(L"Cannot open file ", View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
		return 0;
	}

	ofs.write((char*)&setting, sizeof(Setting));
	
	ofs.close();
	return 1;
}

Setting FileIO::ReadSetting(std::string fileName) {
	ifstream ifs(fileName, ios::binary);

	// if cannot open file
	if (!ifs) {
		View::printCenteredToast(L"Cannot open file ", View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
		return Setting();
	}

	Setting setting;
	ifs.read((char*)&setting, sizeof(Setting));
	ifs.close();

	return setting;
}

std::vector<std::string> FileIO::GetSavedGameList()	{
	std::vector<std::string> savedGameList;
	ifstream ifs(folder + savedGame);
	
	// if cannot open file
	if (!ifs) {
		View::printCenteredToast(L"Cannot open file ", View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
		return savedGameList;
	}

	std::string line;
	while (getline(ifs, line)) {
		savedGameList.push_back(line);
	}

	ifs.close();
	return savedGameList;
}

