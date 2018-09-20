/** 
 * @file code_component.cpp
 * @brief Purpose: Contains all the methods related to code components.
 * 
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#include "code_component.hpp"

using namespace engine;  // Used to avoid write engine::Game engine::Game::instance;.

/**
 * @brief Default constructor for the code component.
 * 
 * @return "void".
*/
CodeComponent::CodeComponent(){}

/**
 * @brief Constructor for the code component.
 *  
 * @param game object to the code component.
 * 
 * @return "void".
*/
CodeComponent::CodeComponent(GameObject &gameObject){
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}

/**
 * @brief inherits function that initialize the game code components
 * 
 * Set all game code components to enable
 * 
 * @return "void".
*/
void CodeComponent::init(){}

/**
 * @brief inherits function that disable the game code components
 * 
 * free the code component pointer
 *  
 * @return "void".
*/
void CodeComponent::shutdown(){}

/**
 * @brief inherits function that update the game code.  
 * 
 * update all the enabled game objects.
 *  
 * @return "void".
*/
void CodeComponent::updateCode(){}
