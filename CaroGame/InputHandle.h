#pragma once
#include <string>
#include <wchar.h>
#include <conio.h>
#include <Windows.h>

namespace InputHandle {
	std::wstring GetKey();
	bool isMoveKey(std::wstring key);
	std::string getFileName(bool checkExisted, SMALL_RECT box);
	bool isValidName(std::string userName);
	std::string getPlayerName(std::string message, std::string player1Name);
}

