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
	// Check AssetsManager to see if image is already loaded.
	auto assets_image = Game::instance.GetAssetsManager().LoadImage(image_path);

	image_texture = assets_image->texture;

	component_width = assets_image->width;
	component_height = assets_image->height;

	renderQuad = {game_object->x, game_object->y, component_width, component_height};
}

void BackgroundComponent::UpdateQuad(){
	renderQuad = {
		game_object->x,
		game_object->y,
		component_width,
		component_height
	};
}


void BackgroundComponent::Shutdown(){
	/* Terminate Texture */
	image_texture = NULL;
}

void BackgroundComponent::Draw(){
	UpdateQuad();

	int successful_draw = SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		image_texture,
		&renderQuad,
		NULL
		);

	if(successful_draw < 0){
		ERROR("Unable to draw.");
	}
}
