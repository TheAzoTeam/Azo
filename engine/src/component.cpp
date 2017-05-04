#include "component.hpp"

engine::Component::Component(){
}

engine::Component::~Component(){
}

bool engine::Component::Init(){
	return true;
}

bool engine::Component::Shutdown(){
	return true;
}