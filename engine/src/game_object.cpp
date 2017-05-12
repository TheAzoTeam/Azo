#include "game_object.hpp"
#include "game.hpp"
#include "code_component.hpp"


using namespace engine;

GameObject::GameObject(){}

GameObject::GameObject(std::string game_object_name){
	this->game_object_name = game_object_name;
};

bool engine::GameObject::Init(SDL_Renderer *){
	for(auto each_pair : component_list){
		auto component = each_pair.second;
		if(component->Init() == false){
			return false;
		}
	}

	return true;
}

bool engine::GameObject::Shutdown(){
	for(auto each_pair : component_list){
		auto component = each_pair.second;
		if(component->Shutdown() == false){
			return false;
		}
	}

	return true;
}

bool engine::GameObject::Draw(SDL_Renderer *){
	for(auto each_pair : component_list){
		if(each_pair.first == typeid(Animation)){
			auto component = each_pair.second;
			(dynamic_cast<Animation *> (component))->UpdateAnimation();
		}

		if(each_pair.first == typeid(CodeComponent)){
			auto component = each_pair.second;
			(dynamic_cast<CodeComponent *> (component))->UpdateCode();
		}
	}
	return true;
}

bool engine::GameObject::AddComponent(engine::Component &component){
	std::pair <std::type_index, Component *> component_pair(typeid(component), &component);

	component_list.insert(component_pair);

	return true;
}
