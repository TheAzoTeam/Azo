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
			int componentWidth;
			int componentHeight;
		public:
			BackgroundComponent();
			BackgroundComponent(std::string imagePath);
			BackgroundComponent(GameObject &gameObject, std::string imagePath);
			~BackgroundComponent();
			void Init();
			void Shutdown();
			void Draw();
			inline std::string GetClassName(){
				return "BackgroundComponent";
			}
	};
}
#endif
