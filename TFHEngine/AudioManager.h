#pragma once
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include "SoundEffect.h"
#include "Song.h"

// stores audio files and allows playback through id's
class AudioManager{
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

private:
	// audio vectors
	std::vector<Song>songList;
	std::vector<SoundEffect>soundFX;
};

