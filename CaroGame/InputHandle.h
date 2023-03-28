#pragma once
#include <string>
#include <wchar.h>
#include <conio.h>

namespace InputHandle {
	std::wstring Get();
	bool isMoveKey(std::wstring key);
	std::string getFileName(bool checkExisted);
	bool isValidUserName(std::string userName);
	std::string getPlayerName(std::string message, std::string player1Name);
}

