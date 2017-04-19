#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "sdl2include.h"
#include <string>

namespace engine {

	enum class GameState {
		EXIT,
		PLAY,
	};

	class Game {
		public:
			Game(std::string game_name, int window_width, int window_heigth);
			void Run();
		private:
			SDL_Window *window;
			SDL_Renderer *canvas;
			GameState game_state;

			std::string game_name;
			int window_width;
			int window_heigth;

			void InitSDL();
			void CreateWindow();
			void TerminateSDL();
	};

}

#endif