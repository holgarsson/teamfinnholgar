#include "AudioManager.h"
#include "Errors.h"

// constructor
AudioManager::AudioManager() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		Error("SDL_mixer could not initialize! SDL_mixer Error: " + *Mix_GetError());
	}
	soundOverlap = false;
}

// destructor
AudioManager::~AudioManager() {
	close();
}

// clean up function
void AudioManager::close() {
	for (int i = 0; i < songList.size(); i++) {
		songList[i]->~Song();
	}
	songList.clear();
	for (int i = 0; i < soundFX.size(); i++) {
		soundFX[i]->~SoundEffect();
	}
	soundFX.clear();
	Mix_Quit();
}

// loads a sound effect in to vector soundFX
bool AudioManager::loadSoundEffect(std::string id, char fileName[]) {
	soundFX.push_back(new SoundEffect(id, fileName));
	if (soundFX.back()->getID() == id) {
		return true;
	}
	else {
		return false;
	}

}

// loads a song in to vector songList
bool AudioManager::loadSong(std::string id, char fileName[]) {
	songList.push_back(new Song(id, fileName));
	if (songList.back()->getID() == id) {
		return true;
	}
	else {
		return false;
	}
}

// if found - plays a sound effect from vector soundFX
void AudioManager::playSound(std::string id) {
	for (int i = 0; i < soundFX.size(); i++) {
		if (soundFX[i]->getID() == id) {
			if (!soundOverlap && Mix_Playing(1)) {
				break;
			}
			else {
				Mix_PlayChannel(-1, soundFX[i]->getSound(), 0);
			}
		}
	}
}

// if found - plays a song from vector songList
// also holds play/resume functionality
void AudioManager::playSong(std::string id) {
	if (id == "stop") {
		Mix_HaltMusic();
	}
	else {
		if (Mix_PlayingMusic() == 0) {
			for (int i = 0; i < songList.size(); i++) {
				if (songList[i]->getID() == id) {
					Mix_PlayMusic(songList[i]->getSong(), -1);
				}
			}
		}
		//If music is being played
		else {
			//If the music is paused
			if (Mix_PausedMusic() == 1)
			{
				//Resume the music
				Mix_ResumeMusic();
			}
			//If the music is playing
			else
			{
				//Pause the music
				Mix_PauseMusic();
			}
		}
	}
}

// set volume for music, 0-128
void AudioManager::setMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}

// set volume for sound effects, 0-128
void AudioManager::setSoundFXVolume(int channel, int volume) {
	Mix_Volume(channel, volume);
}


void AudioManager::setSoundOverlap() {
	if (soundOverlap) {
		soundOverlap = false;
	}
	else {
		soundOverlap = true;
	}
}


bool AudioManager::getSoundOverlap() {
	return soundOverlap;
}

// get volume level
int AudioManager::getMusicVolume() {
	return Mix_VolumeMusic(-1);
}

// get volume level for sound effects (returns volume for final mix channel)
int AudioManager::getSoundFXVolume() {
	return Mix_Volume(-1, -1);
}

// increases the volume of music
void AudioManager::increaseMusicVolume() {
	int volume = Mix_VolumeMusic(-1);
	if (volume < 128) {
		Mix_VolumeMusic(volume + 2);
	}
}

// decreases the volume of music
void AudioManager::lowerMusicVolume() {
	int volume = Mix_VolumeMusic(-1);
	if (volume > 0) {
		Mix_VolumeMusic(volume - 2);
	}
}

// increases the volume of sound effects
void AudioManager::increaseSoundFXVolume() {
	int volume = Mix_Volume(-1, -1);
	if (volume < 128) {
		Mix_Volume(-1, volume + 2);
	}
}

// decreases the volume of sound effects
void AudioManager::lowerSoundFXVolume() {
	int volume = Mix_Volume(-1, -1);
	if (volume > 0) {
		Mix_Volume(-1, volume - 2);
	}
}
