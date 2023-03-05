#include "Sound.h"

void Sound::playSound(LPCWSTR s) {
	// Play the sound track
	PlaySound(s, NULL, SND_FILENAME | SND_ASYNC);
}