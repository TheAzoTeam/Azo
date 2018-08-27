#include "code_component.hpp"


using namespace engine;

CodeComponent::CodeComponent(){}

CodeComponent::CodeComponent(GameObject &game_object){
	this->gameObject = &game_object;
	this->componentState = State::ENABLED;
}

void CodeComponent::Init(){}

void CodeComponent::Shutdown(){}

void CodeComponent::UpdateCode(){}