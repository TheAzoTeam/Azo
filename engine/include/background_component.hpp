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
			std::string imagePath;
			SDL_Texture *imageTexture;
			SDL_Rect renderQuad;
			int component_width;
			int component_height;
		public:
			BackgroundComponent();
			BackgroundComponent(std::string imagePath);
			BackgroundComponent(GameObject &gameObject, std::string imagePath);
			~BackgroundComponent();
			void Init();
			void shutdown();
			void draw();
			inline std::string getClassName(){
				return "BackgroundComponent";
			}
	};
}
#endif
