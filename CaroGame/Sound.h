#pragma comment(lib, "winmm.lib")
#pragma once
#include <Windows.h>

namespace Sound {
	const LPCWSTR VALID = L"D:\\Caro\\Right.wav";
	const LPCWSTR INVALID = L"D:\\Caro\\Error.wav";
	const LPCWSTR BACKGROUND = L"D:\\Caro\\Cipher2.wav";

	struct SoundManager {
		bool onSoundBackGround;
		bool onSoundEffect;
	};

	void playSoundBackGround(SoundManager soundManager);
	void playSoundEffect(LPCWSTR path, SoundManager soundManager);
	void playSound(LPCWSTR path);
}

