#include "animation_controller.hpp"

using namespace engine;

void AnimationController::init(){
	for(auto animation_row : m_animation_map){
		auto animation = animation_row.second;
		animation->init();
	}
}

void AnimationController::draw(){
	for(auto animation_row : m_animation_map){
		auto animation = animation_row.second;
		if(animation->isEnabled()){
			animation->draw();
		}
	}
}

void AnimationController::shutdown(){
	for(auto animation_row : m_animation_map){
		auto animation = animation_row.second;
		animation->shutdown();
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

	if(animation_to_be_played->second->mState == AnimationState::STOPPED){
		for(auto eachAnimation : m_animation_map){
			eachAnimation.second->disableComponent();
			eachAnimation.second->mState = AnimationState::STOPPED;
		}
		if(animation_to_be_played != m_animation_map.end()){
			animation_to_be_played->second->enableComponent();
			animation_to_be_played->second->mState = AnimationState::PLAYING;
		}
	}
}

void AnimationController::StartAnimation(std::string animation_name){
	auto animation_to_be_played = m_animation_map.find(animation_name);

	if(animation_to_be_played == m_animation_map.end()){
		ERROR("Animation " << animation_name << "doesn't exist!");
	}

	if(!animation_to_be_played->second->isEnabled()){
		animation_to_be_played->second->enableComponent();
		animation_to_be_played->second->mState = AnimationState::PLAYING;
	}
}


void AnimationController::StopAnimation(std::string animation_name){
	auto animation_to_be_played = m_animation_map.find(animation_name);

	if(animation_to_be_played != m_animation_map.end()){
		animation_to_be_played->second->disableComponent();
	}else{
		ERROR("Animation couldn't be found!");
	}
}

AnimationState AnimationController::GetAnimationStatus(std::string animation_name){
	auto animation = m_animation_map.find(animation_name);

	if(animation != m_animation_map.end()){
		return animation->second->mState;
	}else{
		ERROR("Animation couldn't be found!");
	}
}