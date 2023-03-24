#include "FileIO.h" 

void FileIO::writeGameInfoToFile(char fileName[], GameInformation game_info) {
	ofstream ofs(fileName, ios::binary);

	if (!ofs) {
		std::cerr << "Cannot open file " << fileName << std::endl;
		return;
	}

	ofs.write((char*)&game_info, sizeof(Model::GameInformation));
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

