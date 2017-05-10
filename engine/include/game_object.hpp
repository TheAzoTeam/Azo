#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <map>
#include "animation.hpp"
#include "sdl2include.h"
#include "component.hpp"
#include "image_component.hpp"

namespace engine {

	class GameObject {
		public:
			GameObject(std::string game_object_name) : game_object_name(game_object_name){};
			virtual bool Init(SDL_Renderer *);
			virtual bool Shutdown();
			virtual bool Draw(SDL_Renderer *);

			bool AddComponent(Component &component);

			inline std::string GetGameObjectName(){
				return game_object_name;
			};

			int x, y;
			int width, height;

		private:
			std::string game_object_name;
			std::map<std::type_index, Component *> component_list;
	};

}

#endif
