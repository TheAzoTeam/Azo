/**
 * @file image_component.cpp
 * @brief Purpose: Contains the components of image fo the game.
 * 
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 * 
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 * 
 * This file implements the main game component its declaration and state.
*/
#include "image_component.hpp"
#include "game.hpp"

using namespace engine;

ImageComponent::ImageComponent() {}

ImageComponent::~ImageComponent() {}

ImageComponent::ImageComponent(GameObject &gameObject, std::string imagePath, double zoomFactor) {
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->zoomFactor = zoomFactor;
}

ImageComponent::ImageComponent(GameObject &gameObject,
			       std::string imagePath,
			       double zoomFactor,
			       std::pair<double, double> position_relative_to_object){
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->zoomFactor = zoomFactor;
	mPositionRelativeToObject = position_relative_to_object;
}

void ImageComponent::init(){
	// Check AssetsManager to see if image is already loaded.
	auto assets_image = Game::instance.getAssetsManager().LoadImage(imagePath);

	imageTexture = assets_image->texture;

	componentWidth = assets_image->width * zoomFactor;
	componentHeight = assets_image->height * zoomFactor;

	gameObject->mSize.first = componentWidth;
	gameObject->mSize.second = componentHeight;

	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + mPositionRelativeToObject.first),
		(int)(gameObject->mCurrentPosition.second + mPositionRelativeToObject.second),
		componentWidth,
		componentHeight
	};

	renderQuad = {0, 0, componentWidth, componentHeight};

}


void ImageComponent::draw(){
	updateQuad();
	SDL_RenderCopy(
		Game::instance.sdlElements.getCanvas(),
		imageTexture,
		&renderQuad,
		&canvasQuad
		);
}

void ImageComponent::updateQuad(){
	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + mPositionRelativeToObject.first),
		(int)(gameObject->mCurrentPosition.second + mPositionRelativeToObject.second),
		componentWidth,
		componentHeight
	};
}
