#include "component.hpp"

using namespace engine;

Component::Component(){}

Component::Component(GameObject &game_object){
	this->game_object = &game_object;
	this->componentState = State::ENABLED;
}

void Component::init(){}

void Component::shutdown(){}


void Component::draw(){}


void Component::updateCode(){}

void Component::enableComponent(){
	this->componentState = State::ENABLED;
}

void Component::disableComponent(){
	this->componentState = State::DISABLED;
}

bool Component::isEnabled(){
	if(componentState == State::ENABLED){
		return true;
	}else{
		return false;
	}
}

