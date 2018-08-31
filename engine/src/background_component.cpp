#include "background_component.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "sdl.hpp"

using namespace engine;


BackgroundComponent::BackgroundComponent(){}

BackgroundComponent::BackgroundComponent(std::string imagePath){
	this->imagePath = imagePath;
	this->component_state = State::ENABLED;
}


BackgroundComponent::BackgroundComponent(GameObject & gameObject, std::string imagePath){
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->component_state = State::ENABLED;
}

BackgroundComponent::~BackgroundComponent(){}

void BackgroundComponent::Init(){
	//DEBUG("BackgroundComponent::Init method.");
	auto assetsImage = Game::instance.GetAssetsManager().LoadImage(imagePath);

	imageTexture = assetsImage->texture;

	componentWidth = assetsImage->width;
	componentHeight = assetsImage->height;

	renderQuad = {0, 0, componentWidth, componentHeight};
}

void BackgroundComponent::Shutdown(){
	/* Terminate Texture */
	imageTexture = NULL;
}

void BackgroundComponent::Draw(){
	//DEBUG("BackgroundComponent::Draw method.");
	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		imageTexture,
		&renderQuad,
		NULL
		);

}
