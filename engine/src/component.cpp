#include "component.hpp"

using namespace engine;

Component::Component(){}

Component::Component(GameObject &gameObject){
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}

void Component::Init(){}

void Component::shutdown(){}


void Component::draw(){}


void Component::UpdateCode(){}

void Component::EnableComponent(){
	this->componentState = State::ENABLED;
}

void Component::disableComponent(){
	this->componentState = State::DISABLED;
}

bool Component::IsEnabled(){
	if(componentState == State::ENABLED){
		return true;
	}else{
		return false;
	}
}
