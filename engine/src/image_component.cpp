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

	canvasQuad = {game_object->x, game_object->y, frame_width, frame_height};
	renderQuad = {0, 0, frame_width, frame_height};

	return true;
}

bool ImageComponent::Shutdown(){
	/* Terminate Texture */
	image_texture = NULL;
	return true;
}

bool ImageComponent::Draw(){

	// Before drawing, set the GameObject sizes so we can calculate collision.
	game_object->game_object_width = frame_width;
	game_object->game_object_height = frame_height;

	game_object->left = game_object->x;
	game_object->right = game_object->x + game_object->game_object_width;
	game_object->top = game_object->y;
	game_object->bottom = game_object->y + game_object->game_object_height;
	//
	// DEBUG("GameObject->left " << game_object->left);
	// DEBUG("GameObject->right " << game_object->right);
	// DEBUG("GameObject->top " << game_object->top);
	// DEBUG("GameObject->bottom " << game_object->bottom);

	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		image_texture,
		&renderQuad,
		&canvasQuad
		);

	return true;
}
