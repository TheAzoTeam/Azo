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
	auto assets_image = Game::instance.GetAssetsManager().LoadImage(imagePath);

	imageTexture = assets_image->texture;

	component_width = assets_image->width;
	component_height = assets_image->height;

	renderQuad = {0, 0, component_width, component_height};
}

void BackgroundComponent::shutdown(){
	/* Terminate Texture */
	imageTexture = NULL;
}

void BackgroundComponent::draw(){
	//DEBUG("BackgroundComponent::draw method.");
	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		imageTexture,
		&renderQuad,
		NULL
		);

}
