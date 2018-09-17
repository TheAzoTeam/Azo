#ifndef SDL_HPP
#define SDL_HPP

#include "log.h"
#include "sdl2include.h"

#include <iostream>
#include <string>


namespace engine {

	// A class that look after all SDL's dependences to run in first.
	class SDL {
        private:
            SDL_Window *window;
            SDL_Renderer *canvas;
            int windowWidth;
            int windowHeight;
            std::string GAME_NAME;

        public:
            SDL();

            // Receive attributes of the Game instance, through "SetGameAttributes" method.
            void SetSDLAttributes(std::string GAME_NAME, int windowWidth, int windowHeight);

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

			// Used to use the private attribute "windowWidth".
		    inline int GetWindowWidth(){
				return windowWidth;
			}

			// Used to use the private attribute "windowHeight".
		    inline int GetWindowHeight(){
				return windowHeight;
			}
    };
}

#endif
