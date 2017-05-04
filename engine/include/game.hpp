#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "sdl2include.h"

#include "scene.hpp"
#include "timer.hpp"
#include "input_manager.hpp"

#include <string>
#include <map>
namespace engine {

	enum class GameState {
		EXIT,
		PLAY,
	};

	class Game {
		public:
			static Game instance;
			Game() :
				need_to_change_scene(false),
				current_scene(NULL),
				last_scene(NULL),
				game_name("Game"),
				window_width(100),
				window_height(100),
				FRAME_RATE(60) {}

			void Run();
			bool AddScene(engine::Scene &scene);
			void SetAttributes(std::string game_name,
					   int window_width,
					   int window_height,
					   int frame_rate);
			inline SDL_Renderer *GetCanvas() {
				return canvas;
			}
		private:
			SDL_Window *window;
			SDL_Renderer *canvas;

			GameState game_state;

			bool need_to_change_scene;

			std::map<std::string, Scene *> scene_map;
			engine::Scene *current_scene;
			engine::Scene *last_scene;

			std::string game_name;
			int window_width;
			int window_height;

			Timer timer;

			int FRAME_RATE;

			void InitSDL();
			void CreateWindow();
			void TerminateSDL();

			void ChangeScene(std::string &scene_name);
			bool StartAndStopScenes();
	};

}

#endif