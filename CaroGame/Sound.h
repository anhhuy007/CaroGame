#pragma comment(lib, "winmm.lib")
#pragma once
#include <Windows.h>
#include <string>

namespace Sound {
	const std::wstring BACKGROUND = L"Sound\\Cipher2.wav";
	const std::wstring VALID = L"Sound\\Right.wav";
	const std::wstring INVALID = L"Sound\\Error.wav";
	const std::wstring WIN = L"Sound\\GameWin.wav";
	const std::wstring LOSE = L"Sound\\Lose.wav";
	const std::wstring MOVE = L"Sound\\Tap.wav";
	const std::wstring CLICK = L"Sound\\Click.wav";
	const std::wstring DRAW = L"Sound\\Draw.wav";

	struct SoundManager {
		bool backgroundSound = true;
		bool effectSound = true;
		bool backgroundPlaying = false;
	};
	void openSound(std::wstring path);
	void playSound(std::wstring path);
	void repeatSound(std::wstring path);
	void stopSound(std::wstring path);
	void pauseSound(std::wstring path);
	void resumeSound(std::wstring path);
	void closeSound(std::wstring path);
	void playBackgroundSound(SoundManager& soundManager);
	void playEffectSound(std::wstring path, SoundManager soundManager);
	std::wstring findAlias(std::wstring path);
	void prepareSound();
}
