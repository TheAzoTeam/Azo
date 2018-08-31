#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "sdl2include.h"
#include "log.h"
#include "scene.hpp"
#include "timer.hpp"
#include "sdl.hpp"
#include "assets_manager.hpp"
#include "input_manager.hpp"

#include <string>
#include <map>


namespace engine {

	// Define Game States to control Loops and other strutuctures.
	enum class GameState {
		EXIT,
		PLAY,
	};

	// Generic Game class. It's how the engine'll see all games that will try to use it.
	class Game {
		public:
			static Game instance;                           // Global game instance that allow access to public attributes and methods in any part of the code.
			SDL sdlElements;                               // Used to access SDL class to take care of sdl elements in game Initialize.
			InputManager inputManager;
			GameState gameState;                           // Define Game States to control Loops and other strutuctures.
		private:
			bool needToChangeScene;                      // Used to define if there's a Change Scene to occur.
			std::map<std::string, Scene *> sceneMap;       // All Scenes of the Game.
			engine::Scene *currentScene;                   // Current Scene.
			engine::Scene *lastScene;                      // Last Scene.
			Timer timer;                                    // Timer to control all Game's Time.
			int frameRate;                                 // Frames per Second of the Game (FPS).
			float frameTime;                               // How many time will have one frame of the Game (miliseconds).
			// TODO(Roger): Move Assets Manager to Scene.
			AssetsManager assetsManager;                   // Manager to load, unload and reference assets.

		public:
			// Constructor Default with default values.
			Game();

			// Used to Initialize the Game in fact (Main Loop).
			void run();

			// Used to add a Scene to map that have all Game's Scenes.
			bool addScene(engine::Scene &scene);

			void restartScene(std::string sceneName);

			/* Used to transfer the gameName, windowWidth and windowHeight to SDL instace through its method
			   "SetSDLAttributes" and set Game's frameRate. */
			void setAttributes(std::string gameName,
					   int windowWidth,
					   int windowHeight,
					   int frameRate);

			// Used to use the private attribute Timer.
			inline Timer& getTimer(){
				return timer;
			}

			// Used to get the private attribute AssetsManager.
			inline AssetsManager& getAssetsManager(){
				return assetsManager;
			}


			// Perform the necessary checks and prepare the structure to switch Scenes.
			void changeScene(std::string sceneName);

		private:
			// Perform scene switching effectively.
			bool startAndStopScenes();

	};
}

#endif
