#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "background_component.hpp"
#include <string>

namespace engine {
	class ImageComponent : public BackgroundComponent {
		protected:
			SDL_Rect canvasQuad;
		public:
			ImageComponent();
			ImageComponent(GameObject &game_object, std::string image_path);
			bool Init();
			bool Draw();
			void UpdateQuad();
			void UpdateGameObjectMeasures();
	};
}

#endif