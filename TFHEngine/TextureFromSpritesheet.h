#pragma once
#include <string>
#include <SDL_image.h>
class TextureFromSpritesheet
{
public:
	TextureFromSpritesheet();
	~TextureFromSpritesheet();

	//Loads image at specified path
	bool loadFromFile(SDL_Renderer* gRenderer, std::string path);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL);

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
