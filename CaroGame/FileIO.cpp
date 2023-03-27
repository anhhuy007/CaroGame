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

// input file name from keyboard 
std::string FileIO::getFileName(bool checkExisted) {
	std::string fileName = "";
	while (1) {
		system("cls");
		// input new file name
		wstring wstr = L"Enter file name: ";
		wstring note = L"(Note: File name must contain only alphabet and number)";
		COORD spot = View::getCenteredSpot(note, View::WINDOW_SIZE);
		View::gotoXY(spot.X, spot.Y + 1);
		wcout << note;
		View::gotoXY(spot.X, spot.Y);
		wcout << wstr;
		cin >> fileName;

		// check if file name is valid
		if (!FileIO::isValidFileName(fileName)) {
			wstr = L"Invalid file name! Please try again.";
			View::printCenteredToast(wstr, View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
			Sleep(1000);
			continue;
		}

		bool isExisted = FileIO::fileNameExisted(fileName);
		
		if (checkExisted == false) {
			// check if file is already exist
			if (isExisted) {
				wstr = L"File is already existed! Please try again.";
				View::printCenteredToast(wstr, View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
				Sleep(1000);
			}
			else {
				break;
			}
		}
		else {
			// check if file is not exist
			if (!isExisted) {
				wstr = L"File is not existed! Please try again.";
				View::printCenteredToast(wstr, View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
				Sleep(1000);
			}
			else {
				break;
			}
		}
	}
	
	return fileName;
}

