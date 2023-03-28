#include "Sound.h"

// play sound
void Sound::playSound(LPCWSTR path) {
	PlaySound(path, NULL, SND_FILENAME | SND_ASYNC);
}

