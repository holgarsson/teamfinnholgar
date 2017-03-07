#include "InputManager.h"
#include <SDL.h>
#include <chrono>
#include <thread>

InputManager::InputManager()
{
	_isAnyKeyPressed = false;
}

InputManager::~InputManager()
{
}

void InputManager::pressKey(unsigned int keyID){
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID){
	_keyMap[keyID] = false;
	_isAnyKeyPressed = false;
}

bool InputManager::isKeyPressed(unsigned int keyID){
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()){
		return it->second;
	}
	else{
		return false;
	}
}

void InputManager::pollInput(){
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)){
		switch (evnt.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			break;
		case SDL_KEYDOWN:
			if (!_isAnyKeyPressed) {
				pressKey(evnt.key.keysym.sym);
				_isAnyKeyPressed = true;
			}
			break;
		case SDL_KEYUP:
			releaseKey(evnt.key.keysym.sym);
			break;
		} // end switch evnt.type
	} // end while
}

bool InputManager::isAnyKeyPressed() {
	return _isAnyKeyPressed;
}