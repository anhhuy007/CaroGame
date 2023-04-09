#include "InputHandle.h"
#include <iostream>
#include "View.h"
#include "FileIO.h"

// this function is used for get the input from keyboard
wstring InputHandle::GetKey() {
	wchar_t ch = _getwch();
	if (ch == 0 || ch == 224) {
		wchar_t temp = _getwch();
		switch (temp) {
		case 59:
			return L"F1";
		case 60:
			return L"F2";
		case 61:
			return L"F3";
		case 62:
			return L"F4";
		case 63:
			return L"F5";
		case 64:
			return L"F6";
		case 65:
			return L"F7";
		case 66:
			return L"F8";
		case 67:
			return L"F9";
		case 68:
			return L"F10";
		case 71:
			return L"HOME";
		case 72:
			return L"UP";
		case 80:
			return L"DOWN";
		case 75:
			return L"LEFT";
		case 77:
			return L"RIGHT";
		}
	}

	switch (ch) {
	case 13:
		return L"ENTER";
	case 27:
		return L"ESC";
	case 8:
		return L"BACKSPACE";
	}
	
	if (ch > 127 || ch < 8) {
		return L"";
	}

	return wstring(1, ch);
}

bool InputHandle::isMoveKey(std::wstring key) {
	return key == L"UP" || key == L"DOWN" || key == L"LEFT" || key == L"RIGHT";
}

// input file name from keyboard 
string InputHandle::GetFileName(bool checkExisted, SMALL_RECT box) {
	string fileName = ""; wstring key = L"";

	wstring wstr = L"Enter file name: ";
	wstring note = L"Note: File name must contain only alphabet and number";
	wstring exitNote = L"Press ESC to exit";
	COORD spot = View::getCenteredSpot(note, box);
	View::printCharactors(note, { spot.X, short(spot.Y + 1) }, View::Color::BLACK, View::Color::WHITE);
	View::printCharactors(exitNote, { spot.X, short(spot.Y + 3) }, View::Color::BLACK, View::Color::WHITE);

	while (1) {
		if (key == L"ENTER") {
			if (fileName != "") {
				system("cls");
				bool isExisted = FileIO::fileNameExisted(fileName);
				
				if (!checkExisted && isExisted) {
					View::printCenteredToast(L"File name is existed!", box, View::Color::BLACK, View::Color::WHITE);
				}
				else if (checkExisted && !isExisted) {
					View::printCenteredToast(L"File name is not existed!", box, View::Color::BLACK, View::Color::WHITE);
				}
				else if (!isValidName(fileName)) {
					View::printCenteredToast(L"File name is invalid!", box, View::Color::BLACK, View::Color::WHITE);
				} 
				else {
					return fileName;
				}

				View::printCharactors(note, { spot.X, short(spot.Y + 1) }, View::Color::BLACK, View::Color::WHITE);
				View::printCharactors(exitNote, { spot.X, short(spot.Y + 3) }, View::Color::BLACK, View::Color::WHITE);
			}
		}
		
		else if (key == L"ESC") {
			return "-1";
		}

		else if (key == L"BACKSPACE") {
			// delete the last character
			View::clearRectangleArea({ short(spot.X + wstr.length()), short(spot.Y) }, 30, 1);
			if (fileName.length() > 0) {
				fileName.pop_back();
			}
		}

		else if (key.length() == 1) {
			// add character
			if (fileName.length() <= 20) {
				fileName += key[0];
			}
		}

		View::gotoXY(spot.X, spot.Y);
		wcout << wstr;
		cout << fileName;
		key = InputHandle::GetKey();
	}
}

bool InputHandle::isValidName(string userName) {
	for (int i = 0; i < userName.length(); i++) {
		userName[i] = tolower(userName[i]);
		if (!isalpha(userName[i]) && !isdigit(userName[i]) && userName[i] != ' ') return false;
	}

	if (userName == "bot" || userName == "computer") return false;
	
	return true;
}

// input player name from keyboard
string InputHandle::GetPlayerName(string message, string player1Name) {
	string fileName = ""; wstring key = L"";
	SMALL_RECT box = View::WINDOW_SIZE;
	wstring note = L"Note: Player name must contain only alphabet and number";
	wstring exitNote = L"Press ESC to exit";
	COORD spot = View::getCenteredSpot(note, box);
	View::printCharactors(note, { spot.X, short(spot.Y + 1) }, View::Color::BLACK, View::Color::WHITE);
	View::printCharactors(exitNote, { spot.X, short(spot.Y + 3) }, View::Color::BLACK, View::Color::WHITE);

	while (1) {
		if (key == L"ENTER") {
			if (fileName != "") {
				system("cls");

				if (fileName == player1Name) {
					View::printCenteredToast(L"Player name must be different from player 1!", box, View::Color::BLACK, View::Color::WHITE);
				}
				else if (!isValidName(fileName)) {
					View::printCenteredToast(L"User name is invalid!", box, View::Color::BLACK, View::Color::WHITE);
				}
				else {
					return fileName;
				}

				View::printCharactors(note, { spot.X, short(spot.Y + 1) }, View::Color::BLACK, View::Color::WHITE);
				View::printCharactors(exitNote, { spot.X, short(spot.Y + 3) }, View::Color::BLACK, View::Color::WHITE);
			}
		}

		else if (key == L"ESC") {
			return "-1";
		}

		else if (key == L"BACKSPACE") {
			// delete the last character
			View::clearRectangleArea({ short(spot.X + message.length()), short(spot.Y) }, 30, 1);
			if (fileName.length() > 0) {
				fileName.pop_back();
			}
		}

		else if (key.length() == 1) {
			// add character
			if (fileName.length() <= 20) {
				fileName += key[0];
			}
		}

		View::gotoXY(spot.X, spot.Y);
		cout << message;
		cout << fileName;
		key = InputHandle::GetKey();
	}
}