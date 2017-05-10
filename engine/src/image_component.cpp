#include "image_component.hpp"
#include "game.hpp"
#include "game_object.hpp"

using namespace engine;


ImageComponent::ImageComponent(){}

ImageComponent::~ImageComponent(){}

bool ImageComponent::Init(){
	/* Load Texture */
	SDL_Surface *image = NULL;

	if(image_path == ""){
		ERROR("Invalid Image Path: " << image_path);
		return false;
	}

	image = IMG_Load(image_path.c_str());

	if(image == NULL){
		ERROR("Couldn't load sprite.");
		return false;
	}

	image_texture = SDL_CreateTextureFromSurface(Game::instance.sdl_elements.GetCanvas(), image);

	if(image_texture == NULL){
		ERROR("Couldn't create texture from image.");
		return false;
	}

	component_width = image->w;
	component_height = image->h;

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
	INFO("Shuting down ImageComponent.");
	SDL_DestroyTexture(image_texture);
	image_texture  = NULL;
	return true;
}

bool ImageComponent::Draw(){

	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		image_texture,
		&renderQuad,
		&canvasQuad
		);

	input_manager.Update();
	if(input_manager.KeyDown(SDL_SCANCODE_W)){
		game_object->y -= 5;
	}
	if(input_manager.KeyDown(SDL_SCANCODE_S)){
		game_object->y += 5;
	}
	if(input_manager.KeyDown(SDL_SCANCODE_D)){
		game_object->x += 5;
		//std::cout << component_width << std::endl;
	}
	if(input_manager.KeyDown(SDL_SCANCODE_A)){
		game_object->x -= 5;
	}

	return true;
}
