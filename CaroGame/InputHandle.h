#pragma once
#include <string>
#include <wchar.h>
#include <conio.h>
#include <Windows.h>

namespace InputHandle {
	// return key pressed on keyboard, including functional keys
	std::wstring GetKey();
	std::string GetFileName(bool checkExisted, SMALL_RECT box);
	std::string GetPlayerName(std::string message, std::string player1Name);
	// check if key is move key (arrow key)
	bool isMoveKey(std::wstring key);
	bool isValidName(std::string userName);
}

