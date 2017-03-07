#include "Window.h"
#include "Errors.h"

Window::Window()
{
}


Window::~Window()
{
	SDL_DestroyWindow(_sdlWindow);
}


int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags){
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	Uint32 flags = SDL_WINDOW_OPENGL;
	if (currentFlags & INVISIBLE){
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & FULLSCREEN){
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & BORDERLESS){
		flags |= SDL_WINDOW_BORDERLESS;
	}


	// Open an SDL Window
	_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	if (_sdlWindow == nullptr){
		fatalError("SDL Window could not be created!");
	}

	// Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
	if (glContext == nullptr){
		fatalError("SDL_GL context could not be created");
	}

	// Set VSYNC (1 = VSYNC on, 0 = VSYNC off)
	SDL_GL_SetSwapInterval(0);

	
	return 0;
}

void Window::swapBuffer(){
	// swap buffer and draw everything on screen
	SDL_GL_SwapWindow(_sdlWindow);
}


int Window::getScreenWidth() { 
	return _screenWidth; 
}

int Window::getScreenHeight() {
	return _screenHeight; 
}

SDL_Window* Window::getWindow() { 
	return _sdlWindow;
}