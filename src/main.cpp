#include <iostream>
#include <SDL.h>

int main(int argc, char *argv[]) {
	bool done = false;
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *win = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	SDL_Event event;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
			case SDL_KEYDOWN:
				done = true;
				break;
			default:
				break;
			}
		}
	}

	SDL_Quit();
	return 0;
}