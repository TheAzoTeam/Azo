#include "input_manager.hpp"

using namespace engine;

InputManager::InputManager(){}
InputManager::~InputManager(){}

bool InputManager::keyDown(Button button) {
	for (auto eachEvent : mEventList) {
		switch(eachEvent.type){
			mLastEventType = eachEvent.type;

			//  Case start.
			case SDL_KEYDOWN:

				if (eachEvent.key.keysym.scancode == (SDL_Scancode)button) {
					return true;
				}

				break;
				// Case end
		}
	}

	return false;
}

bool InputManager::keyDownOnce(Button button) {
	if (keyboardStates[button]) {
		SDL_PumpEvents();
		if (!keyboardStates[button]) {
			return true;
		}
	}
	return false;
}

bool InputManager::keyState(Button button) {
	return keyboardStates[button];
}


void InputManager::clear() {
	mEventList.clear();
}

void InputManager::update(SDL_Event _event) {
	mEventList.push_back(_event);
	keyboardStates = SDL_GetKeyboardState(NULL);
}
