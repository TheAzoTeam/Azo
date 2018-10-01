/**
 * @file sdl.hpp
 * @brief Purpose: Contains general scope to the sdl.
 *
 * GLP v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#ifndef SDL_HPP
#define SDL_HPP

#include <iostream>
#include <string>
#include "log.h"
#include "sdl2include.h"

namespace engine {

	/**
	 * @brief class that look after all SDL's dependences to run in first.
	 *
	 * Class that define the behavior of the sdl.
	 *
	 * @return "void".
	*/
	class SDL {
		private:
			SDL_Window *window;
			SDL_Renderer *canvas;
			int windowWidth;
			int windowHeight;
			std::string gameName;
		public:
			SDL();

			/**
			 * @brief receive attributes of the Game instance through "SetGameAttributes" method.
			 *
			 * @return "void".
			*/
			void setSDLAttributes(std::string gameName, int windowWidth, int windowHeight);

			/**
			 * @brief initialize all SDL.
			 *
			 * Initialize attributes to Windows, Canvas, SDL_IMAGE, SDL_VIDEO, SDL_AUDIO.
			 *
			 * @return "void".
			*/
			void initSDL();

			/**
			 * @brief copy the code where the method is called.
			 *
			 * Used to get Canvas with Inline to be more efficient.
			 *
			 * @return "canvas".
			*/
			inline SDL_Renderer *getCanvas() {
				return canvas;
			}

			/**
			 * @brief creating the Window and Canvas.
			 *
			 * Used inside "Run" method of the Game.
			 *
			 * @return "void".
		    */
			void createWindow();

			/**
			 * @brief terminating SDL.
			 *
	         * Used in the Main Loop's End.
		     *
			 * @return "void".
		    */
			void terminateSDL();

			/**
	         * @brief private attribute "window_width".
		     *
			 * Used to use the private attribute "window_width".
			 *
		     *
			 * @return "window_width".
			*/
			inline int getWindowWidth(){
				return windowWidth;
			}

			/**
			 * @brief private attribute "window_height".
			 *
		     * Used to use the private attribute "window_height".
		     *
			 *
		     * @return "window_height".
			*/
			inline int getWindowHeight(){
				return windowHeight;
			}
	};
}

#endif
