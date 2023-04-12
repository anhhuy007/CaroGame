#include "InputHandle.h"
#include <iostream>
#include "View.h"
#include "FileIO.h"
#include "Sound.h"

// this function is used for get the input from keyboard
std::wstring InputHandle::GetKey() {
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

	return std::wstring(1, ch);
}

bool InputHandle::isMoveKey(std::wstring key) {
	return key == L"UP" || key == L"DOWN" || key == L"LEFT" || key == L"RIGHT";
}

// input file name from keyboard 
std::string InputHandle::GetFileName(bool checkExisted, SMALL_RECT box) {
	std::string fileName = ""; std::wstring key = L"";

	std::wstring wstr = L"Enter file name: ";
	std::wstring note = L"Note: File name must contain only alphabet and number";
	std::wstring exitNote = L"Press ESC to exit";
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
		std::wcout << wstr;
		std::cout << fileName;
		key = InputHandle::GetKey();
	}
}

bool InputHandle::isValidName(std::string userName) {
	for (int i = 0; i < userName.length(); i++) {
		userName[i] = tolower(userName[i]);
		if (!isalpha(userName[i]) && !isdigit(userName[i]) && userName[i] != ' ') return false;
	}

	if (userName == "bot" || userName == "computer") return false;
	
	return true;
}

// input player name from keyboard
std::string InputHandle::GetPlayerName(std::string message, std::string player1Name) {
	std::string fileName = ""; std::wstring key = L"";
	SMALL_RECT box = View::WINDOW_SIZE;
	std::wstring note = L"Note: Player name must contain only alphabet and number";
	std::wstring exitNote = L"Press ESC to exit";
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
		std::cout << message;
		std::cout << fileName;
		key = InputHandle::GetKey();
	}
}

int InputHandle::GetAvatar(std::wstring message) {
	std::wstring key = L"";
	short posX = 5, posY = 5;

	View::printVerticalCenteredCharactors(L"---------- CHOOSE YOUR AVATAR ----------", View::WINDOW_SIZE, 1, View::Color::BLACK, View::Color::WHITE);
	while (key != L"ENTER") {
		short x = 5, y = 5;
		for (int i = 1; i <= 10; i++) {
			View::DrawAvatar(static_cast<View::Avatar>(i), x, y);
			x += 25;
			if (x > 105) {
				x = 5;
				y += 14;
			}
		}

		if (InputHandle::isMoveKey(key)) {
			Sound::playSound(Sound::VALID);
		}

		if (key == L"UP") {
			posY -= 14;
			if (posY < 5) posY = 5;
		}
		else if (key == L"DOWN") {
			posY += 14;
			if (posY > 19) posY = 19;
		}
		else if (key == L"LEFT") {
			posX -= 25;
			if (posX < 5) posX = 5;
		}
		else if (key == L"RIGHT") {
			posX += 25;
			if (posX > 105) posX = 105;
		}

		View::drawBorder3(posX + 5, posX + 26, posY + 2, posY + 12, message);
		key = InputHandle::GetKey();
		View::clearRectangleArea({ posX, posY }, posX + 25, posY + 12);

		if (key == L"ESC") {
			return -1;
		}
	}
		
	system("cls");
	return (posX - 5) / 25 + (posY - 5) / 14 * 5 + 1;
}