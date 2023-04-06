#pragma comment(lib, "winmm.lib")
#pragma once
#include <Windows.h>

namespace Sound {
	const LPCWSTR VALID = L"Sound\\Right.wav";
	const LPCWSTR INVALID = L"Sound\\Error.wav";
	const LPCWSTR BACKGROUND = L"Sound\\Cipher2.wav";
	const LPCWSTR WINGAME2 = L"Sound\\gamewin.wav";

	struct SoundManager {
		bool onSoundBackGround;
		bool onSoundEffect;
	};

	void playSoundBackGround(SoundManager soundManager);
	void playSoundEffect(LPCWSTR path, SoundManager soundManager);
	void playSound(LPCWSTR path);
}
