/**
 * @file code_component.cpp
 * @brief Purpose: Contains all the methods related to code components.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 *
 * This file is responsible for create the model to all code components of the game.
*/
#include "code_component.hpp"
#include "log.h"

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
 * @param Game object to the code component.
 *
 * @return "void".
*/
CodeComponent::CodeComponent(GameObject &gameObject) {
	ASSERT(&gameObject != NULL, "The game object can't be null.");
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
	ASSERT(this->componentState == State::ENABLED, "State must be enabled.");
}

/**
 * @brief Inherits function that initialize the game code components.
 *
 * Set all game code components to enable.
 *
 * @return "void".
*/
void CodeComponent::init(){}

/**
 * @brief Inherits function that disable the game code components.
 *
 * Free the code component pointer.
 *
 * @return "void".
*/
void CodeComponent::shutdown(){}

/**
 * @brief Inherits function that update the game code.
 *
 * Update all the enabled game objects.
 *
 * @return "void".
*/
void CodeComponent::updateCode(){}
