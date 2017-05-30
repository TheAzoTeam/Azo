#include "background_component.hpp"
#include "game.hpp"

using namespace engine;

BackgroundComponent::BackgroundComponent(){}

BackgroundComponent::BackgroundComponent(GameObject &game_object, std::string image_path){
	this->game_object = &game_object;
	this->image_path = image_path;
	this->component_state = State::ENABLED;
}

bool BackgroundComponent::Init(){

	// Check AssetsManager to see if image is already loaded.
	auto assets_image = Game::instance.GetAssetsManager().LoadImage(image_path);

	image_texture = assets_image->texture;

	component_width = assets_image->width;
	component_height = assets_image->height;

	frame_width = component_width;
	frame_height = component_height;

	canvasQuad = {
		game_object->x,
		game_object->y,
		Game::instance.sdl_elements.GetWindowWidth(),
		Game::instance.sdl_elements.GetWindowHeight()
	};

	renderQuad = {0, 0, frame_width, frame_height};

	return true;
}
