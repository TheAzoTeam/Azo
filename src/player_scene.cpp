#include "player_scene.hpp"

PlayerScene::PlayerScene() : engine::Scene("PlayerScene"){
}

PlayerScene::~PlayerScene(){
}

bool PlayerScene::Init(SDL_Renderer *canvas){
	/* Load Texture */
	SDL_Surface *image = NULL;

	image = IMG_Load("sprites/scottpilgrim_multiple.png");

	if(image == NULL){
		std::cout << "Couldn't load sprite." << std::endl;
		return false;
	}

	scene_texture = SDL_CreateTextureFromSurface(canvas, image);

	if(scene_texture == NULL){
		std::cout << "Couldn't create texture from image." << std::endl;
		return false;
	}

	image_w = 0;
	image_h = 0;

	SDL_FreeSurface(image);
	image = NULL;
	/* Finished Loading texture */

	return true;
}

bool PlayerScene::Shutdown(){
	/* Terminate Texture */
	SDL_DestroyTexture(scene_texture);
	scene_texture = NULL;

	return true;
}

bool PlayerScene::Draw(SDL_Renderer *canvas){
	SDL_Rect canvasQuad = {10, 10, 108, 140};;

	SDL_Rect renderQuad = {image_w, image_h, 108, 140};
	SDL_RenderCopy(
		canvas,
		scene_texture,
		&renderQuad,
		&canvasQuad
		);

	return true;
}