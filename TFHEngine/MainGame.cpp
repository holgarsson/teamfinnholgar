#include "MainGame.h"
#include "Errors.h"
#include <iostream>

MainGame::MainGame() :running(true)
{
	Renderer = NULL;
}


MainGame::~MainGame(){
	//Free loaded images
	stickMan.free();
	background.free();

	//Destroy window	
	SDL_DestroyRenderer(Renderer);
	window.~Window();
	Renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void MainGame::init(){
	bool success = true;
	window.create("Alpha Engine", 640, 480, SDL_WINDOW_SHOWN);


	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
		printf("Warning: Linear texture filtering not enabled!");
	}

	// Create renderer for window
	Renderer = SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);
	if (Renderer == NULL){
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}else{
		//Initialize renderer color
		SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	if (!loadSprites()) {
		success = false;
		printf("Failed to load sprites!");
	}
	
	if (!loadSpritesFromSpritesheet()) { 
		success = false;
		printf("Failed to load sprites!");
	}

}

bool MainGame::loadSprites() {
	bool success = true;

	// Load textures
	if (!stickMan.loadFromFile(Renderer, "foo.png")) {
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}
	stickManPosX = (window.getScreenWidth()/2) - (stickMan.getWidth()/2);
	stickManPosY = (window.getScreenHeight()/2) - (stickMan.getHeight()/2);

	// Load background texture
	if (!background.loadFromFile(Renderer, "background.png")) {
		printf("Failed to load background texture image!\n");
		success = false;
	}

	// load soundEffects
	audioManager.loadSoundEffect("scratch", "scratch.wav");
	audioManager.loadSoundEffect("high", "high.wav");
	audioManager.loadSoundEffect("medium", "medium.wav");
	audioManager.loadSoundEffect("low", "low.wav");

	// load Music
	audioManager.loadSong("13 Fighter Beat", "13 Fighter Beat.wav");
	
	return success;
}

bool MainGame::loadSpritesFromSpritesheet() {
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!gSpriteSheetTexture.loadFromFile(Renderer, "11_clip_rendering_and_sprite_sheets/dots.png")) {
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	else {
		//Set top left sprite
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		//Set top right sprite
		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		//Set bottom left sprite
		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		//Set bottom right sprite
		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;
	}

	return success;
}

void MainGame::run(){
	init();
	limiter.setMaxFPS(60.0f);
	
	while (running){
		limiter.begin();

		processInput();
		// updateLogic()

		// Call the custom update and draw method
		if (running) {
			render();
		}
	}
}

void MainGame::processInput(){
	inputManager.pollInput();

	// use char or hex value to represent keys
	if (inputManager.isKeyPressed('q')){ 
		std::cout << 'q' << std::endl; 
	}
	if (inputManager.isKeyPressed('w')){ 
		std::cout << 'w' << std::endl;
		stickManPosY--;
	}
	if (inputManager.isKeyPressed('e')){ 
		std::cout << 'e' << std::endl;
	}
	if (inputManager.isKeyPressed('a')){ 
		std::cout << 'a' << std::endl; 
		stickManPosX--;
	}
	if (inputManager.isKeyPressed('s')){ 
		std::cout << 's' << std::endl; 
		stickManPosY++;
	}
	if (inputManager.isKeyPressed('d')){ 
		std::cout << 'd' << std::endl; 
		stickManPosX++;
	}
	if (inputManager.isKeyPressed(0x20)){ // SPACE
		std::cout << "SPACE" << std::endl;
	}
	if (inputManager.isKeyPressed(0x1B)){ // ESCAPE
		SDL_Quit(); 
		running = false; 
	}

	// keys for audio
	if (inputManager.isKeyPressed('1')) {
		audioManager.playSound("scratch");
		inputManager.releaseKey('1');
	}
	if (inputManager.isKeyPressed('2')) {
		audioManager.playSound("high");
		inputManager.releaseKey('2');
	}
	if (inputManager.isKeyPressed('3')) {
		audioManager.playSound("medium");
		inputManager.releaseKey('3');
	}
	if (inputManager.isKeyPressed('4')) {
		audioManager.playSound("low");
		inputManager.releaseKey('4');
	}
	if (inputManager.isKeyPressed('5')) {
		audioManager.playSound("music");
		inputManager.releaseKey('5');
	}
	if (inputManager.isKeyPressed('6')) {
		audioManager.playSound("stop");
		inputManager.releaseKey('6');
	}
}

void MainGame::render(){
	/* Giti at alt her fer at broytast til spritemanager.renderEverything() ella okkurt */
	
	//system("cls");
	//std::cout << "FPS: " << limiter.end() << std::endl;
	//std::cout << "Pos: X:" << stickManPosX << " Y: " << stickManPosY << std::endl;
	


	
	//Clear screen
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(Renderer);

	/* RENDER FROM IMAGES */
	//Render background texture to screen
	background.render(Renderer, 0, 0);

	//Render Foo' to the screen
	stickMan.render(Renderer, stickManPosX, stickManPosY);



	/* RENDER FROM SPRITESHEET */
	//Render top left sprite
	gSpriteSheetTexture.render(Renderer, 0, 0, &gSpriteClips[0]);

	
	//Render top right sprite
	gSpriteSheetTexture.render(Renderer, window.getScreenWidth() - gSpriteClips[1].w, 0, &gSpriteClips[1]);

	//Render bottom left sprite
	gSpriteSheetTexture.render(Renderer, 0, window.getScreenHeight() - gSpriteClips[2].h, &gSpriteClips[2]);

	//Render bottom right sprite
	gSpriteSheetTexture.render(Renderer, window.getScreenWidth() - gSpriteClips[1].w, window.getScreenHeight() - gSpriteClips[2].h, &gSpriteClips[3]);
	


	//Update screen
	SDL_RenderPresent(Renderer);


}