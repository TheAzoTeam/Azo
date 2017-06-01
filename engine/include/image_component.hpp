#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "background_component.hpp"
#include <string>

namespace engine {
	class ImageComponent : public BackgroundComponent {
		private:
			int pos_x;
			int pos_y;
			SDL_Rect canvasQuad;
		public:
			ImageComponent();
			ImageComponent(GameObject &game_object, std::string image_path, int pos_x, int pos_y);
			bool Init();
			bool Draw();
		private:
			void UpdateGameObjectMeasures();

	};
}

#endif