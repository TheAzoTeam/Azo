#include "background_component.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "sdl.hpp"

using namespace engine;


BackgroundComponent::BackgroundComponent(){}

BackgroundComponent::BackgroundComponent(std::string image_path){
	this->image_path = image_path;
	this->component_state = State::ENABLED;
}


BackgroundComponent::BackgroundComponent(GameObject & game_object, std::string image_path){
	this->game_object = &game_object;
	this->image_path = image_path;
	this->component_state = State::ENABLED;
}

BackgroundComponent::~BackgroundComponent(){}

void BackgroundComponent::Init(){
	//DEBUG("BackgroundComponent::Init method.");
	auto assets_image = Game::instance.GetAssetsManager().LoadImage(image_path);

	image_texture = assets_image->texture;

	component_width = assets_image->width;
	component_height = assets_image->height;

	renderQuad = {0, 0, component_width, component_height};
}

void BackgroundComponent::Shutdown(){
	/* Terminate Texture */
	image_texture = NULL;
}

void BackgroundComponent::Draw(){
	//DEBUG("BackgroundComponent::Draw method.");
	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		image_texture,
		&renderQuad,
		NULL
		);

}
