#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "component.hpp"
#include "sdl2include.h"
#include "input_manager.hpp"

#include <string>
#include <iostream>

namespace engine {

	class ImageComponent : public Component {
		public:
			ImageComponent(GameObject &game_object, std::string image_path) :
				Component(game_object),
				image_path(image_path){}
			ImageComponent();
			~ImageComponent();

			bool Init();
			bool Shutdown();
			bool Draw();
		private:
			InputManager input_manager;
			std::string image_path;
			SDL_Texture *image_texture;
			int component_width;
			int component_height;
	};
}
#endif