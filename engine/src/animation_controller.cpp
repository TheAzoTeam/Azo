/*************************************
@file animation_controller.hpp
@brief Purpose: Contains the animaton controller component.

GPL v3.0 License
Copyright (c) 2017 Azo

Notice: TheAzo, TheAzoTeam
https://github.com/TecProg2018-2/Azo

This file implements the main game component its declaration and state.
*************************************/
#include "animation_controller.hpp"

using namespace engine;

void AnimationController::init(){
	for (auto animationRow : mAnimationMap) {
		auto animation = animationRow.second;
		animation->init();
	}
}

void AnimationController::draw(){
	for (auto animationRow : mAnimationMap) {
		auto animation = animationRow.second;
		if (animation->isEnabled()) {
			animation->draw();
		}
	}
}

void AnimationController::shutdown(){
	for (auto animationRow : mAnimationMap) {
		auto animation = animationRow.second;
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

void AnimationController::addAnimation(std::string animationName, Animation &animation){
	std::pair<std::string, Animation *> newAnimation(animationName, &animation);

	mAnimationMap.insert(newAnimation);
}

void AnimationController::startUniqueAnimation(std::string animationName){
	auto animationToBePlayed = mAnimationMap.find(animationName);

	if (animationToBePlayed == mAnimationMap.end()) {
		ERROR("Animation " << animationName << "doesn't exist!");
	}

	if (animationToBePlayed->second->mState == AnimationState::STOPPED) {
		for (auto eachAnimation : mAnimationMap) {
			eachAnimation.second->disableComponent();
			eachAnimation.second->mState = AnimationState::STOPPED;
		}
		if (animationToBePlayed != mAnimationMap.end()) {
			animationToBePlayed->second->enableComponent();
			animationToBePlayed->second->mState = AnimationState::PLAYING;
		}
	}
}

void AnimationController::startAnimation(std::string animationName){
	auto animationToBePlayed = mAnimationMap.find(animationName);

	if (animationToBePlayed == mAnimationMap.end()) {
		ERROR("Animation " << animationName << "doesn't exist!");
	}

	if (!animationToBePlayed->second->isEnabled()) {
		animationToBePlayed->second->enableComponent();
		animationToBePlayed->second->mState = AnimationState::PLAYING;
	}
}


void AnimationController::stopAnimation(std::string animationName){
	auto animationToBePlayed = mAnimationMap.find(animationName);

	if (animationToBePlayed != mAnimationMap.end()) {
		animationToBePlayed->second->disableComponent();
	} else {
		ERROR("Animation couldn't be found!");
	}
}

AnimationState AnimationController::getAnimationStatus(std::string animationName){
	auto animation = mAnimationMap.find(animationName);

	if (animation != mAnimationMap.end()) {
		return animation->second->mState;
	} else {
		ERROR("Animation couldn't be found!");
	}
}
