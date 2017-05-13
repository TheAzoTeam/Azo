#include "component.hpp"

using namespace engine;

Component::Component(){}

Component::Component(GameObject &game_object){
	this->game_object = &game_object;
	this->component_state = State::ENABLED;
}

Component::~Component(){}

bool Component::Init(){
	return true;
}

bool Component::Shutdown(){
	return true;
}


bool Component::Draw(){
	return true;
}


bool Component::UpdateCode(){
	return true;
}

void Component::EnableComponent(){
	this->component_state = State::ENABLED;
}

void Component::DisableComponent(){
	this->component_state = State::DISABLED;
}

bool Component::IsEnabled(){
	if(component_state == State::ENABLED){
		return true;
	}else{
		return false;
	}
}

