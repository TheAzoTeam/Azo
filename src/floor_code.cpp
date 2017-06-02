#include "floor_code.hpp"

using namespace Azo;

FloorCode::FloorCode(){}

FloorCode::FloorCode(engine::GameObject &game_object){
	this->game_object = &game_object;
}

void FloorCode::UpdateCode(){
	//INFO("Updating FloorCode");
	this->game_object->collision_list.clear();
	game_object->x -= 4;
}