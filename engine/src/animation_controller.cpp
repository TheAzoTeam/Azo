#include "animation_controller.hpp"

using namespace engine;

void AnimationController::Init(){
	for(auto animation_row : m_animation_map){
		auto animation = animation_row.second;
		animation->Init();
	}
}

void AnimationController::Draw(){
	for(auto animation_row : m_animation_map){
		auto animation = animation_row.second;
		if(animation->IsEnabled()){
			animation->Draw();
		}
	}
}

void AnimationController::Shutdown(){
	for(auto animation_row : m_animation_map){
		auto animation = animation_row.second;
		animation->Shutdown();
	}
}

AnimationController::AnimationController(){
	this->componentState = State::ENABLED;
}

AnimationController::AnimationController(GameObject &gameObject){
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}

void AnimationController::AddAnimation(std::string animation_name, Animation &animation){
	std::pair<std::string, Animation *> new_animation(animation_name, &animation);

	m_animation_map.insert(new_animation);
}

void AnimationController::StartUniqueAnimation(std::string animation_name){
	auto animation_to_be_played = m_animation_map.find(animation_name);

	if(animation_to_be_played == m_animation_map.end()){
		ERROR("Animation " << animation_name << "doesn't exist!");
	}

	if(animation_to_be_played->second->m_state == AnimationState::STOPPED){
		for(auto each_animation : m_animation_map){
			each_animation.second->DisableComponent();
			each_animation.second->m_state = AnimationState::STOPPED;
		}
		if(animation_to_be_played != m_animation_map.end()){
			animation_to_be_played->second->EnableComponent();
			animation_to_be_played->second->m_state = AnimationState::PLAYING;
		}
	}
}

void AnimationController::StartAnimation(std::string animation_name){
	auto animation_to_be_played = m_animation_map.find(animation_name);

	if(animation_to_be_played == m_animation_map.end()){
		ERROR("Animation " << animation_name << "doesn't exist!");
	}

	if(!animation_to_be_played->second->IsEnabled()){
		animation_to_be_played->second->EnableComponent();
		animation_to_be_played->second->m_state = AnimationState::PLAYING;
	}
}


void AnimationController::StopAnimation(std::string animation_name){
	auto animation_to_be_played = m_animation_map.find(animation_name);

	if(animation_to_be_played != m_animation_map.end()){
		animation_to_be_played->second->DisableComponent();
	}else{
		ERROR("Animation couldn't be found!");
	}
}

AnimationState AnimationController::GetAnimationStatus(std::string animation_name){
	auto animation = m_animation_map.find(animation_name);

	if(animation != m_animation_map.end()){
		return animation->second->m_state;
	}else{
		ERROR("Animation couldn't be found!");
	}
}
