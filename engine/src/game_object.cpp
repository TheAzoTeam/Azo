/**
 * @file game_object.cpp
 * @brief Purpose: Contains general scope to the game object.
 * 
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 * 
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 * 
 * This file is responsible for create the general model to all game object behavior.
**/
#include "game_object.hpp"
#include "game.hpp"
#include "log.h"
#include "code_component.hpp"

using namespace engine; // Used to avoid write engine::Game engine::Game::instance;.

/**
 * @brief Default constructor for the Game Object component.
 *  
 * @return "void".
*/
GameObject::GameObject(){
	mCenter.first = 0;
	mCenter.second = 0;
	mHalfSize.first = 0;
	mHalfSize.second = 0;
}


/**
 * @brief Constructor for the game object.
 *  
 * @param string that has game object name.
 * @param pair that has the game object current position.
 * 
 * @return "void".
*/
GameObject::GameObject(std::string gameObjectName, std::pair<double, double> currentPosition){
	ASSERT(gameObjectName != "", "The gameObject can't be blank.");
	ASSERT(currentPosition.first <= 0, "The gameObject can't be negative.");
	ASSERT(currentPosition.second <= 0, "The gameObject can't be null.");
	this->mName = gameObjectName;
	this->mCurrentPosition = currentPosition;
}


/**
 * @brief add components to the game.
 *  
 * set the position and insert the game components.
 * 
 * @param component that is added to the game.
 * 
 * @return "void".
*/
void GameObject::addComponent(Component &component){
	ASSERT(&component != NULL, "The component can't be null.");
	std::pair <std::type_index, Component *> componentPair(typeid(component), &component);
	mComponentMap.insert(componentPair);
}


/**
 * @brief retrieve the animation controller.
 *  
 * find and sets the animation controller.
 * 
 * @param index of components that has the component type.
 * 
 * @return the game object Animation Controller.
*/
AnimationController* GameObject::getAnimationController(std::type_index componentType){
	auto componentToBeFound = mComponentMap.find(componentType);

	if (componentToBeFound != mComponentMap.end()){
		DEBUG("AnimationController found. Class name: " << componentToBeFound->second->getClassName());
		return dynamic_cast <AnimationController * > (componentToBeFound->second);
	} else {
		ERROR("Animation Controller couldn't be found!");
	}
}


/**
 * @brief retrieve the audio controller.
 *  
 * find and sets the audio controller.
 * 
 * @param index of components that has the component type.
 * 
 * @return the game object Audio Controller.
*/
AudioController* GameObject::getAudioController(std::type_index componentType){
	ASSERT(&componentType != NULL, "The component type can't be null.");
	auto componentToBeFound = mComponentMap.find(componentType);
	ASSERT(&componentToBeFound != NULL, "The component can't be null.");

	if (componentToBeFound != mComponentMap.end()){
		DEBUG("AudioController found. Class name: " << componentToBeFound->second->getClassName());
		return dynamic_cast <AudioController * > (componentToBeFound->second);
	} else {
		ERROR("Audio Controller couldn't be found!");
	}
}


/**
 * @brief function that initialize the game objects components.
 * 
 * Set all game object components to enable.
 * 
 * @return "void".
*/
void GameObject::init(){
	for (auto eachPair : mComponentMap){
		auto component = eachPair.second;
		if (component->isEnabled()){
			component->init();
		}
	}
}


/**
 * @brief function that draw game objects components.  
 * 
 * draws all the enabled game objects components.
 * 
 * @return "void".
*/
void GameObject::draw(){
	for (auto eachPair : mComponentMap){
		auto component = eachPair.second;

		ASSERT(component != NULL, "Component can't be NULL when drawing.");

		if (component->isEnabled()){
			component->draw();
		}
	}
}


/**
 * @brief function that update the game object code.  
 * 
 * update all the enabled game object components.
 *  
 * @return "void".
*/
void GameObject::updateCode(){
	for (auto eachPair : mComponentMap){
		auto component = eachPair.second;
		if (component->isEnabled()){
			component->updateCode();
		}
	}
}


/**
 * @brief inherits function that disable the game components.
 * 
 * free the component pointers.
 *  
 * @return "void".
*/
void GameObject::shutdown(){}


/**
 * @brief calculate the bottom left coordinate of a game object.
 *  
 * calculate the bottom left coordinate based on its size and half.
 * 
 * @return a pair containing the bottom left coordinate of the game object.
*/
std::pair<double, double> GameObject::calcBottomLeft(){
	std::pair<double, double> bottomLeft;
	bottomLeft.first = mCenter.first - mHalfSize.first;
	bottomLeft.second = mCenter.second + mHalfSize.second;
	return bottomLeft;
}


/**
 * @brief calculate the bottom right coordinate of a game object.
 *  
 * calculate the bottom right coordinate based on its size and half.
 * 
 * @return a pair containing the bottom right coordinate of the game object.
*/
std::pair<double, double> GameObject::calcBottomRight(){
	std::pair<double, double> bottomRight;
	bottomRight.first = mCenter.first + mHalfSize.first;
	bottomRight.second = mCenter.second + mHalfSize.second;
	return bottomRight;
}


/**
 * @brief calculate the top left coordinate of a game object.
 *  
 * calculate the top left coordinate based on its size and half.
 * 
 * @return a pair containing the top left coordinate of the game object.
*/
std::pair<double, double> GameObject::calcTopLeft(){
	std::pair<double, double> topLeft;
	topLeft.first = mCenter.first - mHalfSize.first;
	topLeft.second = mCenter.second - mHalfSize.second;
	return topLeft;
}


/**
 * @brief calculate the top right coordinate of a game object.
 *  
 * calculate the top right coordinate based on its size and half.
 * 
 * @return a pair containing the top right coordinate of the game object.
*/
std::pair<double, double> GameObject::calcTopRight(){
	std::pair<double, double> topRight;
	topRight.first = mCenter.first + mHalfSize.first;
	topRight.second = mCenter.second - mHalfSize.second;
	return topRight;
}


/**
 * @brief calculate the right up coordinate of a game object.
 *  
 * calculate the right up coordinate based on top right coordinate.
 * 
 * @return a pair containing the right up coordinate of the game object.
*/
std::pair<double, double> GameObject::calcRightUp(){
	return calcTopRight();
}


/**
 * @brief calculate the right down coordinate of a game object.
 *  
 * calculate the right down coordinate based on bottom right coordinate.
 * 
 * @return a pair containing the right down coordinate of the game object.
*/
std::pair<double, double> GameObject::calcRightDown(){
	return calcBottomRight();
}


/**
 * @brief calculate the left up coordinate of a game object.
 *  
 * calculate the left up coordinate based on top left coordinate.
 * 
 * @return a pair containing the left up coordinate of the game object.
*/
std::pair<double, double> GameObject::calcLeftUp(){
	return calcTopLeft();
}


/**
 * @brief calculate the left down coordinate of a game object.
 *  
 * calculate the left down coordinate based on bottom left coordinate.
 * 
 * @return a pair containing the left down coordinate of the game object.
*/
std::pair<double, double> GameObject::calcLeftDown(){
	return calcBottomLeft();
}
