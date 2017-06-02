#include "image_component.hpp"
#include "game.hpp"

using namespace engine;

ImageComponent::ImageComponent(){}

ImageComponent::ImageComponent(GameObject &game_object, std::string image_path, int pos_x, int pos_y){
	//DEBUG("Image path on Constructor: " << image_path);
	this->game_object = &game_object;
	this->image_path = image_path;
	this->pos_x = pos_x;
	this->pos_y = pos_y;

}

void ImageComponent::Init(){
	// Check AssetsManager to see if image is already loaded.
	auto assets_image = Game::instance.GetAssetsManager().LoadImage(image_path);

	image_texture = assets_image->texture;

	component_width = assets_image->width;
	component_height = assets_image->height;

	game_object->game_object_width = component_width;

	game_object->game_object_height = component_height;

	canvasQuad = {pos_x, pos_y, component_width, component_height};
	renderQuad = {0, 0, component_width, component_height};
	UpdateGameObjectMeasures();

}

void ImageComponent::Draw(){
	//DEBUG("Image path " << image_path);

	int successful_draw = SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		image_texture,
		&renderQuad,
		&canvasQuad
		);

	if(successful_draw < 0){
		ERROR("Unable to draw.");
	}

}

void ImageComponent::UpdateGameObjectMeasures(){
	// Before drawing, set the GameObject sizes so we can calculate collision.

	game_object->left = game_object->x;
	game_object->right = game_object->x + game_object->game_object_width;
	game_object->top = game_object->y;
	game_object->bottom = game_object->y + game_object->game_object_height;

}

