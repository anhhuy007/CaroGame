#pragma once
#include <string>
#include <wchar.h>
#include <conio.h>

namespace InputHandle {
	std::wstring Get();
	bool isMoveKey(std::wstring key);
}

