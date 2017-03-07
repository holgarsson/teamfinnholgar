#pragma once
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include "SoundEffect.h"
#include "Song.h"

class AudioManager{
public:
	AudioManager();
	~AudioManager();
	void loadSoundEffect(std::string id, char fileName[]);
	void loadSong(std::string id, char fileName[]);
	void close();
	void playSound(std::string id);

private:
	std::vector<Song>songList;
	std::vector<SoundEffect>soundFX;
};

