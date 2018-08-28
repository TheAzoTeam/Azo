#include "component.hpp"

using namespace engine;

Component::Component(){}

Component::Component(GameObject &gameObject){
	this->gameObject = &gameObject;
	this->component_state = State::ENABLED;
}

void Component::Init(){}

void Component::Shutdown(){}


void Component::Draw(){}


void Component::updateCode(){}

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

