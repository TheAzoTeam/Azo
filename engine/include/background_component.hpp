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
			SDL_Rect renderQuad;
			int component_width;
			int component_height;
		public:
			BackgroundComponent();
			BackgroundComponent(std::string image_path);
			BackgroundComponent(GameObject &game_object, std::string image_path);
			~BackgroundComponent();
			void Init();
			void shutdown();
			void Draw();
			inline std::string GetClassName(){
				return "BackgroundComponent";
			}
	};
}
#endif
