#include "code_component.hpp"


using namespace engine;

CodeComponent::CodeComponent(){}

CodeComponent::CodeComponent(GameObject &game_object){
	this->game_object = &game_object;
	this->component_state = State::ENABLED;
}

void CodeComponent::Init(){}

void CodeComponent::shutdown(){}

void CodeComponent::UpdateCode(){}