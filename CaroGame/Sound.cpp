#include "Sound.h"

void playSoundTrack(LPCWSTR s) {
	// Play the sound track
	PlaySound(s, NULL, SND_FILENAME | SND_ASYNC);
	Sleep(300);
	PlaySound(TEXT("D:\\Caro\\Cipher2.wav"), NULL, SND_FILENAME | SND_ASYNC);
}