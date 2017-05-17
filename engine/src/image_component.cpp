#include "image_component.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "sdl.hpp"

using namespace engine;


ImageComponent::ImageComponent(){}

ImageComponent::ImageComponent(GameObject & game_object, std::string image_path){
	this->game_object = &game_object;
	this->image_path = image_path;
	this->component_state = State::ENABLED;
}

ImageComponent::~ImageComponent(){}

bool ImageComponent::Init(){

	// Check AssetsManager to see if image is already loaded.
	auto assets_image = Game::instance.GetAssetsManager().LoadImage(image_path);

	image_texture = assets_image->texture;

	component_width = assets_image->width;
	component_height = assets_image->height;

	frame_width = component_width;
	frame_height = component_height;

	game_object->x = 150;
	game_object->y = 150;

	canvasQuad = {game_object->x, game_object->y, frame_width, frame_height};
	renderQuad = {component_width, component_height, frame_width, frame_height};

	return true;
}

bool ImageComponent::Shutdown(){
	/* Terminate Texture */
	image_texture = NULL;
	return true;
}

bool ImageComponent::Draw(){
	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		image_texture,
		&renderQuad,
		&canvasQuad
		);

	return true;
}
