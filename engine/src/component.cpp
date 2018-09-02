#include "component.hpp"

using namespace engine;

Component::Component(){}

Component::Component(GameObject &gameObject){
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}

void Component::Init(){}

void Component::Shutdown(){}


void Component::Draw(){}


void Component::UpdateCode(){}

void Component::EnableComponent(){
	this->componentState = State::ENABLED;
}

void Component::DisableComponent(){
	this->componentState = State::DISABLED;
}

bool Component::isEnabled(){
	if(componentState == State::ENABLED){
		return true;
	}else{
		return false;
	}
}

