/** 
 * @file component.cpp
 * @brief Purpose: Contains general scope to game components.
 * 
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#include "component.hpp"

using namespace engine; // Used to avoid write engine::Game engine::Game::instance;.

/**
 * @brief Default constructor for the component.
 *  
 * @return "void".
*/
Component::Component(){}

/**
 * @brief Constructor for the component.
 *  
 * @param game object to the component.
 * 
 * @return "void".
*/
Component::Component(GameObject &gameObject){
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}

/**
 * @brief inherits function that initialize the game components
 * 
 * Set all game components to enable
 * 
 * @return "void".
*/
void Component::init(){}

/**
 * @brief inherits function that disable the game components
 * 
 * free the component pointers
 *  
 * @return "void".
*/
void Component::shutdown(){}

/**
 * @brief inherits function that draw game objects. 
 * 
 * draws all the enabled game objects.
 * 
 * @return "void".
*/
void Component::draw(){}

/**
 * @brief inherits function that update the game code.  
 * 
 * update all the enabled game objects.
 *  
 * @return "void".
*/
void Component::updateCode(){}

/**
 * @brief enable components.  
 * 
 * set the game object components state to enabled.
 * 
 * @return "void".
*/
void Component::enableComponent(){
	this->componentState = State::ENABLED;
}

/**
 * @brief disable components.  
 * 
 * set the game object components state to disabled.
 *
 * @return "void".
*/
void Component::disableComponent(){
	this->componentState = State::DISABLED;
}

/**
 * @brief test if component is enable.  
 * 
 * allows see if component is enable or disable.
 * 
 * @return bool that response if component is enabled.
*/
bool Component::isEnabled(){
	if( componentState == State::ENABLED){
		return true;
	} else {
		return false;
	}
}
