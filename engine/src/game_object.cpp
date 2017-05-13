#include "game_object.hpp"
#include "game.hpp"
#include "code_component.hpp"


using namespace engine;

GameObject::GameObject(){}

GameObject::GameObject(std::string game_object_name){
	this->game_object_name = game_object_name;
};

bool engine::GameObject::Init(){
	for(auto each_pair : component_list){
		auto component = each_pair.second;
		if(component->IsEnabled() && component->Init() == false){
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

bool engine::GameObject::Draw(){
	//DEBUG("Number of components: " << component_list.size());
	for(auto each_pair : component_list){
		auto component = each_pair.second;
		if(component->IsEnabled()){
			component->UpdateCode();
			component->Draw();
		}else{
			// Nothing to do.
		}
	}
	return true;
}

bool engine::GameObject::AddComponent(engine::Component &component){
	std::pair <std::type_index, Component *> component_pair(typeid(component), &component);

	component_list.insert(component_pair);

	return true;
}

AnimationController* GameObject::GetComponentByType(std::type_index component_type){
	auto component_to_be_found = component_list.find(component_type);

	if(component_to_be_found != component_list.end()){
		return dynamic_cast <AnimationController * > (component_to_be_found->second);
	}else{
		ERROR("Animation couldn't be found!");
	}
}

