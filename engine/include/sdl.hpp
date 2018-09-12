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
		int windowWidth;
		int windowHeight;
		std::string gameName;
	public:
		SDL();

		// Receive attributes of the Game instance, through "SetGameAttributes" method.
		void setSDLAttributes(std::string gameName, int windowWidth, int windowHeight);

		// Initialize all SDL attributes: Windows, Canvas, SDL_IMAGE, SDL_VIDEO, SDL_AUDIO.
		void initSDL();

		// Used to get Canvas with Inline to be more efficient (Copy the code where the method is called).
		inline SDL_Renderer *getCanvas() {
			return canvas;
		}

		// Used inside "Run" method of the Game, creating the Window and Canvas.
		void createWindow();

		// Used in the Main Loop's End.
		void terminateSDL();

		// Used to use the private attribute "windowWidth".
		inline int getWindowWidth(){
			return windowWidth;
		}

		// Used to use the private attribute "windowHeight".
		inline int getWindowHeight(){
			return windowHeight;
		}
	};
}

#endif
