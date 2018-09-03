#ifndef SDL_HPP
#define SDL_HPP

#include <iostream>
#include <string>
#include "log.h"
#include "sdl2include.h"

namespace engine {
	// A class that look after all SDL's dependences to run in first.
	class SDL {
	private:
		SDL_Window *window;
		SDL_Renderer *canvas;
		int window_width;
		int window_height;
		std::string game_name;

	public:
		SDL();

		// Receive attributes of the Game instance, through "SetGameAttributes" method.
		void SetSDLAttributes(std::string game_name, int window_width, int window_height);

		// Initialize all SDL attributes: Windows, Canvas, SDL_IMAGE, SDL_VIDEO, SDL_AUDIO.
		void InitSDL();

		// Used to get Canvas with Inline to be more efficient (Copy the code where the method is called).
		inline SDL_Renderer *GetCanvas() {
			return canvas;
		}

		// Used inside "Run" method of the Game, creating the Window and Canvas.
		void CreateWindow();

		// Used in the Main Loop's End.
		void TerminateSDL();

		// Used to use the private attribute "window_width".
		inline int GetWindowWidth(){
			return window_width;
		}

		// Used to use the private attribute "window_height".
		inline int GetWindowHeight(){
			return window_height;
		}
	};
}

#endif
