#pragma once
#include "Window.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "FpsLimiter.h"

#include "Texture.h"
#include "TextureFromSpritesheet.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

	void init();
	void run();
	void processInput();
	void render();
	bool loadSprites();
	bool loadSpritesFromSpritesheet();

private:
	bool running;
	Window window;
	InputManager inputManager;
	AudioManager audioManager;
	FpsLimiter limiter;
	SDL_Renderer* Renderer;

	int stickManPosX;
	int stickManPosY;


	// temporary - fer í spritemanager
	// sprites from images
	Texture stickMan;
	Texture background;

	// sprites from sheet
	SDL_Rect gSpriteClips[4];		//Scene sprite
	TextureFromSpritesheet gSpriteSheetTexture;	//Scene sprite
};

