#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "background_component.hpp"
#include <string>

namespace engine {
	class ImageComponent : public BackgroundComponent {
		private:
			std::pair<double, double> m_position_relative_to_object = std::make_pair(0, 0);
		protected:
			int zoom_factor;
			SDL_Rect canvasQuad;
		public:
			std::string image_name = "LIXO";
			ImageComponent();
			ImageComponent(GameObject &game_object, std::string image_path, int zoom_factor);
			ImageComponent(
				GameObject &game_object,
				std::string image_path,
				int zoom_factor,
				std::pair<double, double> position_relative_to_object);
			void Init();
			void Draw();
			void UpdateQuad();
			inline std::string GetClassName(){
				return "ImageComponent";
			}
	};
}

#endif