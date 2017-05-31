#include "floor_code.hpp"

using namespace Azo;

FloorCode::FloorCode(){}

FloorCode::FloorCode(engine::GameObject &game_object){
	this->game_object = &game_object;
}


bool FloorCode::UpdateCode(){
	this->game_object->collision_list.clear();
	return true;
}