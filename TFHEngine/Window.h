#pragma once
#include <SDL.h>
#include <string>

enum WindowFlags{ INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

class Window
{
public:
	Window();
	~Window();

	int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

	void swapBuffer();

	int getScreenWidth();
	int getScreenHeight();

	SDL_Window* getWindow();


private:
	SDL_Window* _sdlWindow;
	SDL_Surface* _ScreenSurface;
	int _screenWidth;
	int _screenHeight;
};
