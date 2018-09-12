#ifndef BACKGROUND_COMPONENT_HPP
#define BACKGROUND_COMPONENT_HPP

#include <string>
#include <iostream>
#include "input_manager.hpp"
#include "component.hpp"
#include "sdl2include.h"
#include "log.h"

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
		void init();
		void shutdown();
		void draw();
		inline std::string getClassName(){
			return "BackgroundComponent";
		}
	};
}

#endif
