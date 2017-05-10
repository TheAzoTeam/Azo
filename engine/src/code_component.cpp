#include "code_component.hpp"


using namespace engine;

bool CodeComponent::Init(){
	return true;
}

bool CodeComponent::Shutdown(){
	return true;
}

bool CodeComponent::UpdateCode(){
	input_manager.Update();

	if(input_manager.KeyDown(SDL_SCANCODE_W)){
		game_object->y -= 3;
	}
	if(input_manager.KeyDown(SDL_SCANCODE_S)){
		game_object->y += 3;
	}
	if(input_manager.KeyDown(SDL_SCANCODE_A)){
		game_object->x -= 6;
	}

	game_object->x += 4;

	if(game_object->x >= Game::instance.sdl_elements.GetWindowWidth()){
		game_object->x = -1 * 108;
	}

	return true;
}
