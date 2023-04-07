#include "Sound.h"
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

void Sound::playBackgroundSound(SoundManager soundManager) {
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
		pauseSound(BACKGROUND);
	}
}

void Sound::playEffectSound(std::wstring path, SoundManager soundManager) {
	if (soundManager.effectSound) playSound(path);
}

void Sound::openSound(wstring path) {
	wstring alias = findAlias(path);
	wstring command = L"open \"" + path + L"\" type mpegvideo alias " + alias;
	mciSendString(command.c_str(), NULL, 0, NULL);
}

void Sound::playSound(wstring path) {
	Sound::openSound(path);
	wstring alias = findAlias(path);
	wstring command = L"play " + alias + L" from 0";
	mciSendString(command.c_str(), 0, 0, 0);
}

void Sound::repeatSound(wstring path) {
	Sound::openSound(path);
	wstring alias = findAlias(path);
	wstring command = L"play " + alias + L" from 0 repeat";
	mciSendString(command.c_str(), 0, 0, 0);
}
void Sound::stopSound(wstring path) {
	wstring alias = findAlias(path);
	wstring command = L"stop " + alias;
	mciSendString(command.c_str(), NULL, 0, NULL);
}

void Sound::pauseSound(wstring path) {
	wstring alias = findAlias(path);
	wstring command = L"pause " + alias;
	cout << mciSendString(command.c_str(), NULL, 0, NULL);
}

void Sound::resumeSound(wstring path) {
	wstring alias = findAlias(path);
	wstring command = L"resume " + alias;
	mciSendString(command.c_str(), NULL, 0, NULL);
}

void Sound::closeSound(wstring path) {
	wstring alias = findAlias(path);
	wstring command = L"close " + alias;
	mciSendString(command.c_str(), NULL, 0, NULL);
}

wstring Sound::findAlias(wstring path) {
	if (path == L"Sound\\Cipher2.wav")
		return L"0";
	if (path == L"Sound\\Right.wav")
		return L"1";
	if (path == L"Sound\\Wrong.wav")
		return L"2";
	if (path == L"Sound\\Win.wav")
		return L"3";
	if (path == L"Sound\\Lose.wav")
		return L"4";
}