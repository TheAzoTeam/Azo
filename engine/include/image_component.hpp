#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include <string>
#include <iostream>

#include "sdl2include.h"
#include "log.h"
#include "component.hpp"
#include "input_manager.hpp"


namespace engine {

	class ImageComponent : public Component {
		protected:
			InputManager input_manager;
			std::string image_path;
			SDL_Texture *image_texture;
			SDL_Rect renderQuad;
			SDL_Rect canvasQuad;
			int component_width;
			int component_height;
			int frame_width;
			int frame_height;

		public:
			ImageComponent(GameObject &game_object, std::string image_path) :
				Component(game_object),
				image_path(image_path){}

			ImageComponent();

			~ImageComponent();

			bool Init();

			bool Shutdown();

			bool Draw();
	};
}
#endif
