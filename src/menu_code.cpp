#include "menu_code.hpp"
#include "game.hpp"

using namespace Azo;

MenuCode::MenuCode(){}

MenuCode::MenuCode(engine::GameObject &game_object){
	this->game_object = &game_object;
}

MenuCode::~MenuCode(){}

bool MenuCode::UpdateCode(){

	if(engine::Game::instance.input_manager.KeyDown(engine::Button::ENTER)){
		DEBUG("Enter pressionado!");
		engine::Game::instance.ChangeScene(global::player_scene);
	}

	return true;
}