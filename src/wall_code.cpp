#include "wall_code.hpp"

using namespace Azo;

WallCode::WallCode(){}

WallCode::WallCode(engine::GameObject &game_object){
	this->game_object = &game_object;
}

bool WallCode::UpdateCode(){
	//INFO("Updating WallCode");
	this->game_object->collision_list.clear();
	game_object->x -= 4;
	return true;
}