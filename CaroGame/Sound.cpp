#include "Sound.h"

// play sound
void Sound::playSoundBackGround(SoundManager soundManager) {
	if (soundManager.onSoundBackGround) {
		PlaySound(BACKGROUND, NULL, SND_FILENAME | SND_ASYNC);
	} 
	else {
		PlaySound(NULL, NULL, 0);
	}
}

void Sound::playSoundEffect(LPCWSTR path, SoundManager soundManager) {
	if (soundManager.onSoundEffect) {
		PlaySound(path, NULL, SND_FILENAME | SND_ASYNC);
	}
}

void Sound::playSound(LPCWSTR path) {
	PlaySound(path, NULL, SND_FILENAME | SND_ASYNC);
}
