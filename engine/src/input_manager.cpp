#include "input_manager.hpp"

using namespace engine;

InputManager::InputManager(){}
InputManager::~InputManager(){}

bool InputManager::KeyDown(Button button){
	for(auto each_event : m_event_list){
		switch(each_event.type){
			m_last_event_type = each_event.type;

			//  Case start.
			case SDL_KEYDOWN:

				if(each_event.key.keysym.scancode == (SDL_Scancode)button){
					return true;
				}

				break;
				// Case end
		}
	}

	return false;
}

bool InputManager::KeyDownOnce(Button button){
	if(keyboard_states[button]){
		SDL_PumpEvents();
		if(!keyboard_states[button]){
			return true;
		}
	}
	return false;
}

bool InputManager::KeyState(Button button){
	return keyboard_states[button];
}


void InputManager::clear(){
	m_event_list.clear();
}

void InputManager::update(SDL_Event _event){
	m_event_list.push_back(_event);
	keyboard_states = SDL_GetKeyboardState(NULL);
}
