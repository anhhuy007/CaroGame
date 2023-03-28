#include "Sound.h"

// play sound
void Sound::playSound(LPCWSTR path, bool onSound) {
	if (!onSound) return;
	PlaySound(path, NULL, SND_FILENAME | SND_ASYNC);
}

