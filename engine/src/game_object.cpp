#include "game_object.hpp"
#include "game.hpp"
#include "code_component.hpp"


using namespace engine;

GameObject::GameObject(){}

GameObject::GameObject(std::string game_object_name){
	this->game_object_name = game_object_name;
};

bool GameObject::Init(){
	for(auto component : component_list){
		if(component->Init() == false){
			return false;
		}
	}

	return true;
}

bool GameObject::Shutdown(){
	for(auto component : component_list){
		if(component->Shutdown() == false){
			return false;
		}
	}

	return true;
}

bool GameObject::Draw(){
	for(auto component : component_list){
		component->Draw();
		component->UpdateCode();
	}

	return true;
}

bool GameObject::AddComponent(engine::Component &component){
	component_list.push_back(&component);
	return true;
}
