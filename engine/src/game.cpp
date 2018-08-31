#include "sdl2include.h"
#include "game.hpp"
#include <iostream>
#include <cstdlib>

using namespace engine; // Used to avoid write engine::Game engine::Game::instance;.

Game Game::instance;    // Used to Initialize in fact the static instance of game;

Game::Game(){
	this->needToChangeScene = false;
	this->currentScene = NULL;
	this->lastScene = NULL;
	this->frameRate = 60;
}

// Main Game Loop and SDL Initiators.
void Game::run(){

	// (SDL) Initialize all SDL attributes: Windows, Canvas, SDL_IMAGE, SDL_VIDEO, SDL_AUDIO.
	sdlElements.InitSDL();

	// (SDL) Create Window and Canvas.
	sdlElements.CreateWindow();

	// (STATE) Set game state to show that it's running.
	gameState = engine::GameState::PLAY;

	// Calculate how many time will have one frame of the Game (miliseconds).
	frameTime = 1000.0f / frameRate;


	INFO("Starting Main Loop Game.");
	while(gameState == engine::GameState::PLAY){

		// Get the current time.
		timer.Step();

		if(startAndStopScenes() == false){
			break;
		}

		// Reading input (events).
		SDL_Event _event;

		// "Search" for a event that will close the Game.
		while(SDL_PollEvent(&_event)){
			switch(_event.type){
				case SDL_QUIT:
					// (STATE) Set game state to show that it'll Die.
					gameState = engine::GameState::EXIT;
					break;
				default:
					// Check for user inputs.
					inputManager.Update(_event);
					break;
			}
		}

		// Clean and Draw the Scene to refreh animations and objects.
		// DEBUG("Drawing current scene.");
		// DEBUG("Scene name: " << currentScene->GetSceneName());
		SDL_RenderClear(sdlElements.GetCanvas());
		currentScene->Draw();
		SDL_RenderPresent(sdlElements.GetCanvas());

		//DEBUG("Updating current scene: " << currentScene->GetSceneName() << " code.");
		currentScene->UpdateCode();


		//INFO("Clearing user input from InputManager.");
		inputManager.Clear();

		//INFO("Calculating elapsed time from the start of this frame until now");
		timer.DeltaTime();

		/* If the time that has passed until now was faster than the frame's time, is needed wait
		   the time necessary to complete a frame's time.*/
		if(frameTime > timer.GetDeltaTime()){
			SDL_Delay(frameTime - timer.GetDeltaTime());
		}

		timer.DeltaTime();

	}

	INFO("Finishing Main Loop.");

	INFO("Shutting down SDL.");
	sdlElements.TerminateSDL();
}


// Used to add a Scene to map that have all Game's Scenes.
bool Game::addScene(Scene &scene){
	auto scene_name = scene.GetSceneName();


	if(sceneMap.find(scene_name) != sceneMap.end()){
		ERROR("Scene already exists!");
		return false;
	}else{
		// Nothing to Do.
	}

	sceneMap[scene_name] = &scene;

	return true;
}

void Game::restartScene(std::string scene_name){
	auto scene = sceneMap[scene_name];

	scene->Restart();
}


// Perform the necessary checks and prepare the structure to switch Scenes.
void Game::changeScene(std::string scene_name){
	INFO("Changing Scenes.");
	if(sceneMap.find(scene_name) == sceneMap.end()){
		ERROR("Scene not found!");
	}else{
		// Nothing to Do.
	}

	lastScene = currentScene;
	currentScene = sceneMap[scene_name];
	needToChangeScene = true;
}


// Perform scene switching effectively.
bool Game::startAndStopScenes(){
	if(needToChangeScene){
		if(currentScene == NULL){
			ERROR("No scenes to run!");
			return false;
		}else{

			// If the last scene is equal the current scene, we still need
			// to delete all keys from the game object map on scene.
			if(lastScene != NULL && lastScene->GetSceneName() == currentScene->GetSceneName()){
				currentScene->DeleteKeyList();
			}

			if(currentScene->m_state == SceneState::RUNNED){
				currentScene->Restart();
				currentScene->m_state = SceneState::FIRST_TIME;
			}

			if(currentScene->m_state == SceneState::FIRST_TIME){
				currentScene->m_state = SceneState::RUNNED;
			}


			currentScene->Init();

			if(lastScene != NULL){
				INFO("Shuting down scene!");
				if(lastScene->GetSceneName() != currentScene->GetSceneName()){
					lastScene->Shutdown();
				}
				//DEBUG("Scene name: " << lastScene->GetSceneName());
				//sceneMap.erase(lastScene->GetSceneName());
			}else{
				// Nothing to Do.
			}

			needToChangeScene = false;
		}
	}

	return true;
}


/* Transfer the game_name, windowWidth and windowHeight to SDL instace through its method "SetSDLAttributes"
   and set Game's frameRate. */
void Game::setAttributes(std::string game_name, int windowWidth, int windowHeight, int frameRate){
	sdlElements.SetSDLAttributes(game_name, windowWidth, windowHeight);
	this->frameRate = frameRate;
}
