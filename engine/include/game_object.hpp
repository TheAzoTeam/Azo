#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "sdl2include.h"
#include <iostream>

namespace engine {

	class GameObject {
		public:
			GameObject(std::string game_object_name) : game_object_name(game_object_name){
			};
			virtual bool Init(SDL_Renderer *);
			virtual bool Shutdown();
			virtual bool Draw(SDL_Renderer *);

			inline std::string GetGameObjectName(){
				return game_object_name;
			};

			int x, y;
			int width, height;

		private:
			std::string game_object_name;
	};

}

#endif