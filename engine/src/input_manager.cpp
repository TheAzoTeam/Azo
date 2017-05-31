#include "input_manager.hpp"

using namespace engine;

InputManager::InputManager(){}
InputManager::~InputManager(){}

bool InputManager::KeyDown(SDL_Scancode scan_code){
	Update();
	return keyboard_states[scan_code];
}

void InputManager::Update(){
	keyboard_states = SDL_GetKeyboardState(NULL);
}