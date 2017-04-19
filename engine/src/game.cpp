#include "sdl2include.h"
#include "game.hpp"
#include <iostream>
#include <cstdlib>

engine::Game::Game(std::string game_name, int window_width, int window_heigth){
	this->game_name = game_name;
	this->window_width = window_width;
	this->window_heigth = window_heigth;

	InitSDL();
	game_state = engine::GameState::PLAY;
}


/* Initializing SDL */
void engine::Game::InitSDL(){

	/* Audio and video */
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
		std::cout << "SDL Video or SDL Audio couldn't be started." << std::endl;
		std::exit(EXIT_FAILURE);
	}
	/* Initializing SDL Image */

	int image_flags = IMG_INIT_PNG;

	if(!IMG_Init(image_flags) & image_flags){
		std::cout << "SDL Image could't be started." << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void engine::Game::CreateWindow(){
	/* Create Window */

	window = SDL_CreateWindow(
		game_name.c_str(),      // Game window title
		SDL_WINDOWPOS_CENTERED, // Window opening position x.
		SDL_WINDOWPOS_CENTERED, // Window opening position y.
		window_width,           // Window width
		window_heigth,          // Window height
		SDL_WINDOW_SHOWN
		);

	if(window == NULL){
		std::cout << "Couldn't create window." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	/* Create Canvas */

	canvas = SDL_CreateRenderer(
		window,                         // Window pointer
		-1,                             // The index to the rendering driver, or -1 to the first one
		SDL_RENDERER_ACCELERATED        // Flag. The renderer will use hardware acceleration
		);

	if(canvas == NULL){
		std::cout << "Couldn't create renderer." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	/* Set window color when redrawing */

	SDL_SetRenderDrawColor(
		canvas, // Renderer pointer
		0xff,   // Red color
		0xff,   // Green color
		0xff,   // Blue color
		0xff);  // Opacity (alpha)
}

/* Game loop */
void engine::Game::Run(){
	/* Create Window */
	CreateWindow();

	/* Load Texture */

	SDL_Texture *play_button_texture = NULL;

	SDL_Surface *image = NULL;

	image = IMG_Load("sprites/scottpilgrim_multiple.png");

	if(image == NULL){
		std::cout << "Couldn't load sprite." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	play_button_texture = SDL_CreateTextureFromSurface(canvas, image);

	if(play_button_texture == NULL){
		std::cout << "Couldn't create texture from image." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	int sprite_size_h = 0;
	int sprite_size_w = 0;

	SDL_FreeSurface(image);
	image = NULL;

	/* Finished Loading texture */

	/* Main Loop */
	while(game_state == engine::GameState::PLAY){

		/* Reading input (events) */
		SDL_Event _event;

		while(SDL_PollEvent(&_event)){
			switch(_event.type){
				case SDL_QUIT:
					game_state = engine::GameState::EXIT;
					break;
				case SDL_KEYDOWN:
					switch(_event.key.keysym.sym){
						case SDLK_a:
							break;
						case SDLK_d:
							sprite_size_w = (sprite_size_w + 108) % 864;
							break;
						default:
							break;
					}
				default:
					break;
			}

			/* Draw */
			SDL_RenderClear(canvas);
			SDL_Rect canvasQuad = {10, 10, 108, 140};
			SDL_Rect renderQuad = {sprite_size_w, sprite_size_h, 108, 140};
			SDL_RenderCopy(
				canvas,
				play_button_texture,
				&renderQuad,
				&canvasQuad
				);
			SDL_RenderPresent(canvas);
		}
	}

	/* Finishing Main Loop */

	/* Terminate Texture */

	SDL_DestroyTexture(play_button_texture);
	play_button_texture = NULL;

	/* Shutdown SDL */
	TerminateSDL();

}

/* Shutdown */
void engine::Game::TerminateSDL(){
	SDL_DestroyRenderer(canvas);
	canvas = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();

	SDL_Quit();
}