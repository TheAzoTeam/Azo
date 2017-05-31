#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "background_component.hpp"
#include <string>

namespace engine {
	class ImageComponent : public BackgroundComponent {
		private:
			int component_width;
			int component_height;
		protected:
			SDL_Rect renderQuad;
			SDL_Rect canvasQuad;
		public:
			ImageComponent();
			ImageComponent(GameObject &game_object, std::string image_path);
			bool Init();
			bool Draw();
			void UpdateGameObjectMeasures();
	};
}

#endif