#pragma once
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include "SoundEffect.h"
#include "Song.h"

// stores audio files and allows playback through id's
class AudioManager {
public:
	// constructor
	AudioManager();

	// destructor
	~AudioManager();

	// clean up function
	void close();

	// load audio into vectors
	bool loadSoundEffect(std::string id, char fileName[]);
	bool loadSong(std::string id, char fileName[]);

	// play audio from vector
	void playSound(std::string id);
	void playSong(std::string id);

	// volume functions
	void setSoundOverlap();
	void setSoundFXVolume(int channel, int volume);
	void setMusicVolume(int volume);
	void increaseSoundFXVolume();
	void increaseMusicVolume();
	void lowerSoundFXVolume();
	void lowerMusicVolume();
	bool getSoundOverlap();
	int getSoundFXVolume();
	int getMusicVolume();

private:
	bool soundOverlap;
	// audio vectors
	std::vector<Song*>songList;
	std::vector<SoundEffect*>soundFX;
};

