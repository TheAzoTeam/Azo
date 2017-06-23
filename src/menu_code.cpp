#include "game.hpp"
#include "menu_code.hpp"

using namespace Azo;

MenuCode::MenuCode(engine::GameObject *game_object){
	this->game_object = game_object;
}

void MenuCode::UpdateCode(){
	if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){
		engine::Game::instance.ChangeScene("level_one");
	}
}