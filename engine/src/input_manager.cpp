#include "input_manager.hpp"

engine::InputManager::InputManager(){}
engine::InputManager::~InputManager(){}

bool engine::InputManager::KeyDown(SDL_Scancode scan_code){
	return keyboard_states[scan_code];
}

void engine::InputManager::Update(){
	keyboard_states = SDL_GetKeyboardState(NULL);
}