#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "sdl2include.h"
#include "scene.hpp"
#include <string>
#include <map>
namespace engine {

	enum class GameState {
		EXIT,
		PLAY,
	};

	class Game {
		public:
			Game(std::string game_name, int window_width, int window_heigth);

			void Run();
			bool AddScene(Scene &scene);
		private:
			SDL_Window *window;
			SDL_Renderer *canvas;
			GameState game_state;

			std::map<std::string, Scene *> scene_map;
			Scene *current_scene;
			Scene *last_scene;

			std::string game_name;
			int window_width;
			int window_heigth;

			void InitSDL();
			void CreateWindow();
			void TerminateSDL();

			void ChangeScene(std::string &scene_name);
			bool StartAndStopScenes();
	};

}

#endif