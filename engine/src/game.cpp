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
		timer.step();

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
					inputManager.update(_event);
					break;
			}
		}

		// Clean and Draw the Scene to refreh animations and objects.
		// DEBUG("Drawing current scene.");
		// DEBUG("Scene name: " << currentScene->getSceneName());
		SDL_RenderClear(sdlElements.GetCanvas());
		currentScene->draw();
		SDL_RenderPresent(sdlElements.GetCanvas());

		//DEBUG("Updating current scene: " << currentScene->getSceneName() << " code.");
		currentScene->updateCode();


		//INFO("Clearing user input from InputManager.");
		inputManager.clear();

		//INFO("Calculating elapsed time from the start of this frame until now");
		timer.deltaTime();

		/* If the time that has passed until now was faster than the frame's time, is needed wait
		   the time necessary to complete a frame's time.*/
		if(frameTime > timer.getDeltaTime()){
			SDL_Delay(frameTime - timer.getDeltaTime());
		}

		timer.deltaTime();

	}

	INFO("Finishing Main Loop.");

	INFO("Shutting down SDL.");
	sdlElements.TerminateSDL();
}


// Used to add a Scene to map that have all Game's Scenes.
bool Game::addScene(Scene &scene){
	auto sceneName = scene.getSceneName();


	if(sceneMap.find(sceneName) != sceneMap.end()){
		ERROR("Scene already exists!");
		return false;
	}else{
		// Nothing to Do.
	}

	sceneMap[sceneName] = &scene;

	return true;
}

void Game::restartScene(std::string sceneName){
	auto scene = sceneMap[sceneName];

	scene->restart();
}


// Perform the necessary checks and prepare the structure to switch Scenes.
void Game::changeScene(std::string sceneName){
	INFO("Changing Scenes.");
	if(sceneMap.find(sceneName) == sceneMap.end()){
		ERROR("Scene not found!");
	}else{
		// Nothing to Do.
	}

	lastScene = currentScene;
	currentScene = sceneMap[sceneName];
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
			if(lastScene != NULL && lastScene->getSceneName() == currentScene->getSceneName()){
				currentScene->deleteKeyList();
			}

			if(currentScene->mState == SceneState::RUNNED){
				currentScene->restart();
				currentScene->mState = SceneState::FIRST_TIME;
			}

			if(currentScene->mState == SceneState::FIRST_TIME){
				currentScene->mState = SceneState::RUNNED;
			}


			currentScene->init();

			if(lastScene != NULL){
				INFO("Shuting down scene!");
				if(lastScene->getSceneName() != currentScene->getSceneName()){
					lastScene->shutdown();
				}
				//DEBUG("Scene name: " << lastScene->getSceneName());
				//sceneMap.erase(lastScene->getSceneName());
			}else{
				// Nothing to Do.
			}

			needToChangeScene = false;
		}
	}

	return true;
}


/* Transfer the gameName, windowWidth and windowHeight to SDL instace through its method "SetSDLAttributes"
   and set Game's frameRate. */
void Game::setAttributes(std::string gameName, int windowWidth, int windowHeight, int frameRate){
	sdlElements.SetSDLAttributes(gameName, windowWidth, windowHeight);
	this->frameRate = frameRate;
}
