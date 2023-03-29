#include "InputHandle.h"
#include <iostream>
#include "View.h"
#include "FileIO.h"
using namespace std;

// this function is used for get the input from keyboard
// there are 6 main types of input: UP, DOWN, LEFT, RIGHT, ENTER, ESC
wstring InputHandle::Get() {
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
string InputHandle::getFileName(bool checkExisted, SMALL_RECT box) {
	string fileName = "";
	while (1) {
		// input new file name
		wstring wstr = L"Enter file name: ";
		wstring note = L"Note: File name must contain only alphabet and number";
		wstring exitNote = L"Type 'esc' to exit";
		COORD spot = View::getCenteredSpot(note, box);
		View::gotoXY(spot.X, spot.Y + 1);
		wcout << note;
		View::gotoXY(spot.X, spot.Y + 2);
		wcout << exitNote;
		View::gotoXY(spot.X, spot.Y);
		wcout << wstr;
		cin >> fileName;

		// check exit
		if (fileName == "esc") {
			return "-1";
		}

		View::clearRectangleArea({ short(spot.X - 5), short(spot.Y) }, 100, 3);

		// check if file name is valid
		if (!FileIO::isValidFileName(fileName)) {
			wstr = L"Invalid file name! Please try again.";
			View::printCenteredToast(wstr, box, View::Color::BLACK, View::Color::WHITE);
			continue;
		}

		bool isExisted = FileIO::fileNameExisted(fileName);

		if (checkExisted == false) {
			// check if file is already exist
			if (isExisted) {
				wstr = L"File is already existed! Please try again.";
				View::printCenteredToast(wstr, box, View::Color::BLACK, View::Color::WHITE);
			}
			else {
				break;
			}
		}
		else {
			// check if file is not exist
			if (!isExisted) {
				wstr = L"File is not existed! Please try again.";
				View::printCenteredToast(wstr, box, View::Color::BLACK, View::Color::WHITE);
			}
			else {
				break;
			}
		}

		View::clearRectangleArea({ short(spot.X - 5), short(spot.Y - 1) }, 100, 2);
	}

	return fileName;
}

bool InputHandle::isValidUserName(string userName) {
	for (int i = 0; i < userName.length(); i++) {
		if (!isalpha(userName[i]) && !isdigit(userName[i])) return false;
	}

	if (userName == "bot" || userName == "computer") return false;
	
	return true;
}

// input user name from keyboard
string InputHandle::getPlayerName(string message, string player1Name) {
	std::string userName = ""; wstring wstr = L"";
	while (1) {
		// input new user name
		wstring note = L"Note: User name must contain only alphabet and number";
		wstring exitNote = L"Type 'esc' to exit";
		COORD spot = View::getCenteredSpot(note, View::WINDOW_SIZE);
		View::gotoXY(spot.X, spot.Y + 1);
		wcout << note;
		View::gotoXY(spot.X, spot.Y + 2);
		wcout << exitNote;
		View::gotoXY(spot.X, spot.Y);
		cout << message;
		cin >> userName;

		// check if returning back 
		if (userName == "esc") {
			return "-1";
		}

		// clear the input area
		View::clearRectangleArea({ short(spot.X - 20), short(spot.Y) }, 100, 3);

		// check if user name is valid
		if (!InputHandle::isValidUserName(userName)) {
			wstr = L"Invalid user name! Please try again.";
			View::printCenteredToast(wstr, View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
			continue;
		}

		// check if user name is already exist
		if (userName == player1Name) {
			wstr = L"User name is already existed! Please try again.";
			View::printCenteredToast(wstr, View::WINDOW_SIZE, View::Color::BLACK, View::Color::WHITE);
		}
		else {
			break;
		}

		COORD spot1 = View::getCenteredSpot(note, View::WINDOW_SIZE);
		View::clearRectangleArea({ short(spot1.X - 20), short(spot1.Y - 1) }, 100, 2);
	}

	return userName;
}