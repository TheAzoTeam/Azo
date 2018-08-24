#include "component.hpp"

using namespace engine;

Component::Component(){}


Component::Component(GameObject &game_object){
	this->game_object = &game_object;
	this->component_state = State::ENABLED;
}


void Component::init(){}


void Component::shutdown(){}


void Component::draw(){}


void Component::updateCode(){}


void Component::enableComponent(){
	this->component_state = State::ENABLED;
}


void Component::disableComponent(){
	this->component_state = State::DISABLED;
}


bool Component::isEnabled(){
	if( component_state == State::ENABLED){
		return true;
	} else {
		return false;
	}
}

