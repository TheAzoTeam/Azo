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
#include "animation_controller.hpp"


namespace engine {

	class GameObject {
		public:
			GameObject();
			GameObject(std::string game_object_name);

			virtual bool Init();
			virtual bool Shutdown();
			virtual bool Draw();

			bool AddComponent(Component &component);

			inline std::string GetGameObjectName(){
				return game_object_name;
			};

			AnimationController* GetComponentByType(std::type_index component_type);

			int x, y;
			int width, height;

		protected:
			std::string game_object_name;
			std::map<std::type_index, Component *> component_list;
	};

}

#endif
