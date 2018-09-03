#include "animation_controller.hpp"

using namespace engine;

void AnimationController::Init(){
	for(auto animation_row : m_animation_map){
		auto animation = animation_row.second;
		animation->Init();
	}
}

void AnimationController::draw(){
	for(auto animation_row : m_animation_map){
		auto animation = animation_row.second;
		if(animation->IsEnabled()){
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

void AnimationController::AddAnimation(std::string animationName, Animation &animation){
	std::pair<std::string, Animation *> new_animation(animationName, &animation);

	m_animation_map.insert(new_animation);
}

void AnimationController::StartUniqueAnimation(std::string animationName){
	auto animation_to_be_played = m_animation_map.find(animationName);

	if(animation_to_be_played == m_animation_map.end()){
		ERROR("Animation " << animationName << "doesn't exist!");
	}

	if(animation_to_be_played->second->mState == AnimationState::STOPPED){
		for(auto each_animation : m_animation_map){
			each_animation.second->disableComponent();
			each_animation.second->mState = AnimationState::STOPPED;
		}
		if(animation_to_be_played != m_animation_map.end()){
			animation_to_be_played->second->EnableComponent();
			animation_to_be_played->second->mState = AnimationState::PLAYING;
		}
	}
}

void AnimationController::StartAnimation(std::string animationName){
	auto animation_to_be_played = m_animation_map.find(animationName);

	if(animation_to_be_played == m_animation_map.end()){
		ERROR("Animation " << animationName << "doesn't exist!");
	}

	if(!animation_to_be_played->second->IsEnabled()){
		animation_to_be_played->second->EnableComponent();
		animation_to_be_played->second->mState = AnimationState::PLAYING;
	}
}


void AnimationController::StopAnimation(std::string animationName){
	auto animation_to_be_played = m_animation_map.find(animationName);

	if(animation_to_be_played != m_animation_map.end()){
		animation_to_be_played->second->disableComponent();
	}else{
		ERROR("Animation couldn't be found!");
	}
}

AnimationState AnimationController::GetAnimationStatus(std::string animationName){
	auto animation = m_animation_map.find(animationName);

	if(animation != m_animation_map.end()){
		return animation->second->mState;
	}else{
		ERROR("Animation couldn't be found!");
	}
}
