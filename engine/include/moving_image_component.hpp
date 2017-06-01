#ifndef MOVING_IMAGE_COMPONENT_HPP
#define MOVING_IMAGE_COMPONENT_HPP

#include "background_component.hpp"
#include <string>

namespace engine {
	class MovingImageComponent : public BackgroundComponent {
		protected:
			SDL_Rect canvasQuad;
		public:
			MovingImageComponent();
			MovingImageComponent(GameObject &game_object, std::string image_path);
		public:
			bool Init();
			bool Draw();
			void UpdateQuad();
			void UpdateGameObjectMeasures();

	};
}

#endif