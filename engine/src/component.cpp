/**
 * @file component.cpp
 * @brief Purpose: Contains general scope to game components.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 *
 * This file is responsible for create the model to all components of the game.
*/
#include "component.hpp"
#include "log.h"

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
 * @param Game object to the component.
 *
 * @return "void".
*/
Component::Component(GameObject &gameObject){
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");
	this->componentState = State::ENABLED;
	ASSERT(this->componentState == State::ENABLED, "Must change component state.");
}

/**
 * @brief Inherits function that initialize the game components
 *
 * Set all game components to enable
 *
 * @return "void".
*/
void Component::init(){}

/**
 * @brief Inherits function that disable the game components
 *
 * Free the component pointers
 *
 * @return "void".
*/
void Component::shutdown(){}

/**
 * @brief Inherits function that draw game objects.
 *
 * Draws all the enabled game objects.
 *
 * @return "void".
*/
void Component::draw(){}

/**
 * @brief Inherits function that update the game code.
 *
 * Update all the enabled game objects.
 *
 * @return "void".
*/
void Component::updateCode(){}

/**
 * @brief Enable components.
 *
 * Set the game object components state to enabled.
 *
 * @return "void".
*/
void Component::enableComponent(){
	this->componentState = State::ENABLED;
	ASSERT(this->componentState == State::ENABLED, "Must change component state.");
}

/**
 * @brief Disable components.
 *
 * Set the game object components state to disabled.
 *
 * @return "void".
*/
void Component::disableComponent(){
	this->componentState = State::DISABLED;
	ASSERT(this->componentState == State::ENABLED, "Must change component state.");
}

/**
 * @brief Test if component is enable.
 *
 * Allows see if component is enable or disable.
 *
 * @return Bool that response if component is enabled.
*/
bool Component::isEnabled(){
	if (componentState == State::ENABLED) {
		return true;
	} else {
		return false;
	}
}
