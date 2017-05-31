#ifndef BACKGROUND_COMPONENT_HPP
#define BACKGROUND_COMPONENT_HPP

#include <string>
#include <iostream>

#include "sdl2include.h"
#include "log.h"
#include "component.hpp"
#include "input_manager.hpp"

namespace engine {

	class BackgroundComponent : public Component {
		protected:
			std::string image_path;
			SDL_Texture *image_texture;

		public:
			BackgroundComponent();

			BackgroundComponent(GameObject &game_object, std::string image_path);

			~BackgroundComponent();

			bool Init();

			bool Shutdown();

			bool Draw();
	};
}
#endif
