#include "AudioManager.h"
#include "Errors.h"
#include <iostream>

// constructor
AudioManager::AudioManager(){
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

// destructor
AudioManager::~AudioManager(){
	close();
}

// clean up function
void AudioManager::close() {
	Mix_Quit();
}

// loads a sound effect in to vector soundFX
bool AudioManager::loadSoundEffect(std::string id, char fileName[]) {
	soundFX.push_back(SoundEffect(id, fileName));
	if (soundFX.back().getID() == id) {
		return true;
	}
	else {
		return false;
	}

}

// loads a song in to vector songList
bool AudioManager::loadSong(std::string id, char fileName[]) {
	songList.push_back(Song(id, fileName));
	if (songList.back().getID() == id) {
		return true;
	}
	else {
		return false;
	}
}

// if found - plays a sound effect from vector soundFX
void AudioManager::playSound(std::string id) {
	for (int i = 0; i < soundFX.size(); i++) {
		if (soundFX[i].getID() == id) {
			if (Mix_Playing(-1)) {
				break;
			}
			else {
				Mix_PlayChannel(-1, soundFX[i].sound, 0);
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
				if (songList[i].getID() == id) {
					Mix_PlayMusic(songList[i].song, -1);
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
