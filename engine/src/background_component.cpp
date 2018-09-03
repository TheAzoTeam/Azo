#include "background_component.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "sdl.hpp"

using namespace engine;

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
	auto assetsImage = Game::instance.GetAssetsManager().LoadImage(imagePath);
	imageTexture = assetsImage->texture;
	componentWidth = assetsImage->width;
	componentHeight = assetsImage->height;
	renderQuad = {0, 0, componentWidth, componentHeight};
}

void BackgroundComponent::shutdown(){
	/* Terminate Texture */
	imageTexture = NULL;
}

void BackgroundComponent::draw(){
	//DEBUG("BackgroundComponent::draw method.");
	SDL_RenderCopy(
		Game::instance.sdl_elements.getCanvas(),
		imageTexture,
		&renderQuad,
		NULL
	);
}
