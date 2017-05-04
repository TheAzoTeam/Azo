#include "player_object.hpp"

bool PlayerObject::Init(SDL_Renderer *canvas){
	/* Load Texture */
	SDL_Surface *image = NULL;

	image = IMG_Load("sprites/scottpilgrim_multiple.png");

	if(image == NULL){
		std::cout << "Couldn't load sprite." << std::endl;
		return false;
	}

	player_object_texture = SDL_CreateTextureFromSurface(canvas, image);

	if(player_object_texture == NULL){
		std::cout << "Couldn't create texture from image." << std::endl;
		return false;
	}

	width = 0;
	height = 0;

	SDL_FreeSurface(image);
	image = NULL;
	/* Finished Loading texture */

	return true;
}

bool PlayerObject::Draw(SDL_Renderer *canvas){
	SDL_Rect canvasQuad = {10, 10, 108, 140};;

	SDL_Rect renderQuad = {width, height, 108, 140};
	SDL_RenderCopy(
		canvas,
		player_object_texture,
		&renderQuad,
		&canvasQuad
		);

	return true;
}

bool PlayerObject::Shutdown(){
	/* Terminate Texture */
	SDL_DestroyTexture(player_object_texture);
	player_object_texture = NULL;

	return true;
}