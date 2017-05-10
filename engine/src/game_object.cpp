#include "game_object.hpp"
#include "game.hpp"


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
	}
	return true;
}

bool engine::GameObject::AddComponent(engine::Component &component){
	std::pair <std::type_index, Component *> component_pair(typeid(component), &component);

	component_list.insert(component_pair);

	return true;
}
