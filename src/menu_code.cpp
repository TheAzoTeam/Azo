#include "menu_code.hpp"
#include "game.hpp"

using namespace Azo;

MenuCode::MenuCode(){}

MenuCode::~MenuCode(){}

bool MenuCode::UpdateCode(){
	DEBUG("MenuCode::UpdateCode");
	input_manager.Update();

	if(input_manager.KeyDown(SDL_SCANCODE_RETURN)){
		DEBUG("Enter pressionado!");
		engine::Game::instance.ChangeScene(global::player_scene);
	}

	return true;
}

void MenuCode::SetGameObject(engine::GameObject &game_object){
	this->game_object = &game_object;
}