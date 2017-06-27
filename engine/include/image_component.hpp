#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "background_component.hpp"
#include <string>

namespace engine {
	class ImageComponent : public BackgroundComponent {
		protected:
			int zoom_factor;
			SDL_Rect canvasQuad;
		public:
			ImageComponent();
			ImageComponent(GameObject &game_object, std::string image_path, int zoom_factor);
			void Init();
			void Draw();
			void UpdateQuad();
			inline std::string GetClassName(){
				return "ImageComponent";
			}
	};
}

#endif