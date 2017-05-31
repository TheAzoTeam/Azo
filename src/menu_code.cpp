#include "menu_code.hpp"
#include "game.hpp"

using namespace Azo;

MenuCode::MenuCode(){}

MenuCode::MenuCode(engine::GameObject &game_object){
	this->game_object = &game_object;
}

MenuCode::~MenuCode(){}

bool MenuCode::UpdateCode(){

	if(input_manager.KeyDown(SDL_SCANCODE_RETURN)){
		DEBUG("Enter pressionado!");
		engine::Game::instance.ChangeScene(global::player_scene);
	}

	return true;
}