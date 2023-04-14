#include "Sound.h"
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <string>

void Sound::playBackgroundSound(SoundManager& soundManager) {
	if (soundManager.backgroundSound) {
		if (soundManager.backgroundPlaying) {
			resumeSound(BACKGROUND);
		}
		else {
			repeatSound(BACKGROUND);
			soundManager.backgroundPlaying = true;
		}
	} 
	else {
		soundManager.backgroundPlaying = false;
		pauseSound(BACKGROUND);
	}
}

void Sound::playEffectSound(std::wstring path, SoundManager soundManager) {
	if (soundManager.effectSound) playSound(path);
}

void Sound::openSound(std::wstring path) {
	std::wstring alias = findAlias(path);
	std::wstring command = L"open \"" + path + L"\" type mpegvideo alias " + alias;
	mciSendString(command.c_str(), NULL, 0, NULL);
}

void Sound::playSound(std::wstring path) {
	Sound::openSound(path);
	std::wstring alias = findAlias(path);
	std::wstring command = L"play " + alias + L" from 0";
	mciSendString(command.c_str(), 0, 0, 0);
}

void Sound::repeatSound(std::wstring path) {
	Sound::openSound(path);
	std::wstring alias = findAlias(path);
	std::wstring command = L"play " + alias + L" from 0 repeat";
	mciSendString(command.c_str(), 0, 0, 0);
}
void Sound::stopSound(std::wstring path) {
	std::wstring alias = findAlias(path);
	std::wstring command = L"stop " + alias;
	mciSendString(command.c_str(), NULL, 0, NULL);
}

void Sound::pauseSound(std::wstring path) {
	std::wstring alias = findAlias(path);
	std::wstring command = L"pause " + alias;
	mciSendString(command.c_str(), NULL, 0, NULL);
}

void Sound::resumeSound(std::wstring path) {
	std::wstring alias = findAlias(path);
	std::wstring command = L"resume " + alias;
	mciSendString(command.c_str(), NULL, 0, NULL);
}

void Sound::closeSound(std::wstring path) {
	std::wstring alias = findAlias(path);
	std::wstring command = L"close " + alias;
	mciSendString(command.c_str(), NULL, 0, NULL);
}

std::wstring Sound::findAlias(std::wstring path) {
	if (path == L"Sound\\Cipher2.wav")
		return L"0";
	if (path == L"Sound\\Right.wav")
		return L"1";
	if (path == L"Sound\\Wrong.wav")
		return L"2";
	if (path == L"Sound\\GameWin.wav")
		return L"3";
	if (path == L"Sound\\Lose.wav")
		return L"4";
	if (path == L"Sound\\Tap.wav")
		return L"5";
}

void Sound::prepareSound() {
	Sound::openSound(Sound::BACKGROUND);
	Sound::openSound(Sound::INVALID);
	Sound::openSound(Sound::VALID);
	Sound::openSound(Sound::MOVE);
	Sound::openSound(Sound::WIN);
	Sound::openSound(Sound::LOSE);
}