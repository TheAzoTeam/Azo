#ifndef SCENE_ENGINE_HPP
#define SCENE_ENGINE_HPP

#include <iostream>
#include "sdl2include.h"

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

		protected:
			std::string scene_name;
			SDL_Texture *scene_texture;
			int image_w, image_h;
	};
}

#endif