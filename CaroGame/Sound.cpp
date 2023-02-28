#include "Sound.h"

void playSound(LPCWSTR s) {
	// Play the sound track
	PlaySound(s, NULL, SND_FILENAME | SND_ASYNC);
	Sleep(400);
	PlaySound(TEXT("D:\\Caro\\Cipher2.wav"), NULL, SND_FILENAME | SND_ASYNC);
}