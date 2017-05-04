#include "sdl2include.h"
#include "game.hpp"
#include <iostream>
#include <cstdlib>

engine::Game engine::Game::instance;

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
		window_height,          // Window height
		SDL_WINDOW_SHOWN
		);

	if(window == NULL){
		std::cout << "Couldn't create window." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	/* Create Canvas */
	canvas = SDL_CreateRenderer(
		window,                                                 // Window pointer
		-1,                                                     // The index to the rendering driver, or -1 to the first one
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC    // Flag. The renderer will use hardware acceleration
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

	InitSDL();
	game_state = engine::GameState::PLAY;

	/* Create Window */
	CreateWindow();

	/* Main Loop */
	while(game_state == engine::GameState::PLAY){

		timer.Step();

		if(StartAndStopScenes() == false){
			break;
		}
		/* Reading input (events) */
		SDL_Event _event;


		while(SDL_PollEvent(&_event)){
			switch(_event.type){
				case SDL_QUIT:
					game_state = engine::GameState::EXIT;
					break;
				default:
					break;
			}

			if(timer.DeltaTime() >= 1.0f / FRAME_RATE){}
			/* Draw */
			SDL_RenderClear(canvas);
			current_scene->Draw(canvas);
			SDL_RenderPresent(canvas);
		}
	}
/* Finishing Main Loop */

/* Shutdown SDL */
	TerminateSDL();

}

bool engine::Game::AddScene(Scene &scene){
	auto scene_name = scene.GetSceneName();

	if(scene_map.find(scene_name) != scene_map.end()){
		std::cout << "Scene already exists!" << std::endl;
		return false;
	}

	scene_map[scene_name] = &scene;

	if(current_scene == NULL){
		std::cout << "Null current scene! Changing Scenes!" << std::endl;
		ChangeScene(scene_name);
	}

	return true;
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

void engine::Game::ChangeScene(std::string &scene_name){
	if(scene_map.find(scene_name) == scene_map.end()){
		std::cout << "Scene not found!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	last_scene = current_scene;
	current_scene = scene_map[scene_name];
	need_to_change_scene = true;
}

bool engine::Game::StartAndStopScenes(){
	if(need_to_change_scene){
		if(current_scene == NULL){
			std::cout << "No scenes to run!" << std::endl;
			return false;
		}else{
			if(last_scene != NULL){
				std::cout << "Shuting down scene!" << std::endl;
				last_scene->Shutdown();
			}
			current_scene->Init(canvas);

			need_to_change_scene = false;
		}
	}
	return true;
}

void engine::Game::SetAttributes(std::string game_name, int window_width, int window_height, int frame_rate){
	this->game_name = game_name;
	this->window_width = window_width;
	this->window_height = window_height;
	this->FRAME_RATE = frame_rate;
}