/*************************************
@file background_component.hpp
@brief Purpose: Contains the components of the background images.

GPL v3.0 License
Copyright (c) 2017 Azo

Notice: TheAzo, TheAzoTeam
https://github.com/TecProg2018-2/Azo

This file implements the main game component its declaration and state.
*************************************/
#include "background_component.hpp"
/*************************************
@file game_object.hpp
@brief Purpose: Contains the game objects.

GPL v3.0 License
Copyright (c) 2017 Azo

Notice: TheAzo, TheAzoTeam
https://github.com/TecProg2018-2/Azo

This file implements the main game component its declaration and state.
*************************************/
#include "game_object.hpp"
/*************************************
@file game.hpp
@brief Purpose: Contains the Game class declaration.

GPL v3.0 License
Copyright (c) 2017 Azo

Notice: TheAzo, TheAzoTeam
https://github.com/TecProg2018-2/Azo

This file implements the main game component its declaration and state.
*************************************/
#include "game.hpp"
/**
 * @file sdl.hpp
 * @brief Purpose: Contains general scope to the sdl.
 *
 * GLP v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#include "sdl.hpp"

using namespace engine;

const int COMPONENT_X = 0;
const int COMPONENT_Y = 0;

BackgroundComponent::BackgroundComponent(){}

BackgroundComponent::BackgroundComponent(std::string imagePath){
	this->imagePath = imagePath;
	this->componentState = State::ENABLED;
}

BackgroundComponent::BackgroundComponent(GameObject & gameObject, std::string imagePath){
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->componentState = State::ENABLED;
}

BackgroundComponent::~BackgroundComponent(){}

void BackgroundComponent::init(){
	//DEBUG("BackgroundComponent::init method.");
	auto assetsImage = Game::instance.getAssetsManager().LoadImage(imagePath);
	imageTexture = assetsImage->texture;
	componentWidth = assetsImage->width;
	componentHeight = assetsImage->height;
	renderQuad = {COMPONENT_X, COMPONENT_Y, componentWidth, componentHeight};
}

void BackgroundComponent::shutdown(){
	// Terminate Texture
	imageTexture = NULL;
}

void BackgroundComponent::draw(){
	//DEBUG("BackgroundComponent::draw method.");
	SDL_RenderCopy(
		Game::instance.sdlElements.getCanvas(),
		imageTexture,
		&renderQuad,
		NULL
	);
}
