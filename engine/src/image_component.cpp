#include "image_component.hpp"
#include "game.hpp"

engine::ImageComponent::ImageComponent(){}

engine::ImageComponent::~ImageComponent(){}


bool engine::ImageComponent::Init(){
	/* Load Texture */
	SDL_Surface *image = NULL;

	if(image_path == ""){
		std::cout << "Invalid Image Path." << std::endl;
		return false;
	}

	image = IMG_Load(image_path.c_str());

	if(image == NULL){
		std::cout << "Couldn't load sprite." << std::endl;
		return false;
	}

	image_texture = SDL_CreateTextureFromSurface(engine::Game::instance.GetCanvas(), image);

	if(image_texture == NULL){
		std::cout << "Couldn't create texture from image." << std::endl;
		return false;
	}

	component_width = 0;
	component_height = 0;

	game_object->x = 150;
	game_object->y = 150;


	return true;
}

bool engine::ImageComponent::Shutdown(){
	/* Terminate Texture */
	std::cout << "Shuting down ImageComponent" << std::endl;
	SDL_DestroyTexture(image_texture);
	image_texture  = NULL;
	return true;
}

bool engine::ImageComponent::Draw(){
	SDL_Rect canvasQuad = {game_object->x, game_object->y, 108, 140};

	SDL_Rect renderQuad = {component_width, component_height, 108, 140};


	SDL_RenderCopy(
		engine::Game::instance.GetCanvas(),
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
		component_width = (component_width + 108) % 864;
		//std::cout << component_width << std::endl;
	}
	if(input_manager.KeyDown(SDL_SCANCODE_A)){
		game_object->x -= 5;
	}

	return true;
}
