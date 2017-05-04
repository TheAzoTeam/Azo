#ifndef SCENE_ENGINE_HPP
#define SCENE_ENGINE_HPP

#include <iostream>
#include "sdl2include.h"
#include "game_object.hpp"
#include <map>

namespace engine {
	class Scene {
		public:
			Scene(std::string scene_name) : scene_name(scene_name) {
			};
			~Scene(){
			};

			virtual bool Init(SDL_Renderer *canvas);
			virtual bool Shutdown();
			virtual bool Draw(SDL_Renderer *canvas);

			inline std::string GetSceneName() {
				return scene_name;
			}

			bool AddGameObject(engine::GameObject &game_object);
			engine::GameObject & GetGameObject(std::string & game_object_name);
			bool RemoveGameObject(std::string &game_object_name);

		protected:
			std::map<std::string, engine::GameObject *> game_object_map;
			std::string scene_name;
			int image_w, image_h;
	};
}

#endif