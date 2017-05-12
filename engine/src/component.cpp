#include "component.hpp"

using namespace engine;

Component::Component(){}

Component::Component(GameObject &game_object){
	this->game_object = &game_object;
}

Component::~Component(){}

bool Component::Init(){
	return true;
}

bool Component::Shutdown(){
	return true;
}