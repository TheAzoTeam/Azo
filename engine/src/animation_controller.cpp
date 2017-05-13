#include "animation_controller.hpp"

using namespace engine;

bool AnimationController::Init(){
	for(auto animation_row : animation_map){
		auto animation = animation_row.second;
		animation->Init();
	}

	return true;
}


bool AnimationController::Draw(){
	for(auto animation_row : animation_map){
		auto animation = animation_row.second;
		if(animation->IsEnabled()){
			animation->Draw();
		}
	}
	return true;
}

bool AnimationController::Shutdown(){
	for(auto animation_row : animation_map){
		auto animation = animation_row.second;
		animation->Shutdown();
	}
	return true;
}

AnimationController::AnimationController(){
	this->component_state = State::ENABLED;
}

AnimationController::AnimationController(GameObject &game_object){
	this->game_object = &game_object;
	this->component_state = State::ENABLED;
}

void AnimationController::AddAnimation(std::string animation_name, Animation &animation){
	std::pair<std::string, Animation *> new_animation(animation_name, &animation);

	animation_map.insert(new_animation);
}

void AnimationController::StartAnimation(std::string animation_name){

	auto animation_to_be_played = animation_map.find(animation_name);

	if(animation_to_be_played != animation_map.end()){
		animation_to_be_played->second->EnableComponent();

	}else{
		// Nothing to do.
	}
}

void AnimationController::StopAnimation(std::string animation_name){
	auto animation_to_be_played = animation_map.find(animation_name);

	if(animation_to_be_played != animation_map.end()){
		animation_to_be_played->second->DisableComponent();
	}else{
		ERROR("Animation couldn't be found!");
	}
}


