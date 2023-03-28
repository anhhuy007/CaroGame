#pragma comment(lib, "winmm.lib")
#pragma once
#include <Windows.h>

namespace Sound {
	const LPCWSTR right = L"D:\\Caro\\Right.wav";
	const LPCWSTR error = L"D:\\Caro\\Error.wav";
	const LPCWSTR background = L"D:\\Caro\\Cipher2.wav";

	void playSound(LPCWSTR path, bool onSound);
}

