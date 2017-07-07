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
			static Game instance;                           /* Global game instance that allow access to public attributes and methods in any part of the code.*/
			SDL sdl_elements;                               // Used to access SDL class to take care of sdl elements in game Initialize.
			InputManager input_manager;
			GameState game_state;                           // Define Game States to control Loops and other strutuctures.
		private:
			bool need_to_change_scene;                      // Used to define if there's a Change Scene to occur.
			std::map<std::string, Scene *> scene_map;       // All Scenes of the Game.
			engine::Scene *current_scene;                   // Current Scene.
			engine::Scene *last_scene;                      // Last Scene.
			Timer timer;                                    // Timer to control all Game's Time.
			int frame_rate;                                 // Frames per Second of the Game (FPS).
			float frame_time;                               // How many time will have one frame of the Game (miliseconds).
			// TODO(Roger): Move Assets Manager to Scene.
			AssetsManager assets_manager;                   // Manager to load, unload and reference assets.

		public:
			// Constructor Default with default values.
			Game();

			// Used to Initialize the Game in fact (Main Loop).
			void Run();

			// Used to add a Scene to map that have all Game's Scenes.
			bool AddScene(engine::Scene &scene);

			void RestartScene(std::string scene_name);

			/* Used to transfer the game_name, window_width and window_height to SDL instace through its method
			   "SetSDLAttributes" and set Game's frame_rate. */
			void SetAttributes(std::string game_name,
					   int window_width,
					   int window_height,
					   int frame_rate);

			// Used to use the private attribute Timer.
			inline Timer& GetTimer(){
				return timer;
			}

			// Used to get the private attribute AssetsManager.
			inline AssetsManager& GetAssetsManager(){
				return assets_manager;
			}


			// Perform the necessary checks and prepare the structure to switch Scenes.
			void ChangeScene(std::string scene_name);

		private:
			// Perform scene switching effectively.
			bool StartAndStopScenes();

	};
}

#endif
