#pragma once
#include <SDL_image.h>
#include <string>

//Texture wrapper class
class Texture {
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool loadFromFile(SDL_Renderer* gRenderer, std::string path);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(SDL_Renderer* gRenderer, int x, int y);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};
