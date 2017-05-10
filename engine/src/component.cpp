#include "component.hpp"

using namespace engine;

Component::Component(){}

Component::~Component(){}

bool Component::Init(){
	return true;
}

bool Component::Shutdown(){
	return true;
}

void Component::EnableComponent(){
	component_state = State::ENABLED;
}

void Component::DisableComponent(){
	component_state = State::DISABLED;
}