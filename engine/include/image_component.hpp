#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "background_component.hpp"
#include <string>

namespace engine {
	class ImageComponent : public BackgroundComponent {
		protected:
			std::pair<double, double> mPositionRelativeToObject = std::make_pair(0, 0);
			double zoomFactor;
			SDL_Rect canvasQuad;
		public:
			ImageComponent();
			virtual ~ImageComponent();
			ImageComponent(GameObject &gameObject,
						   std::string imagePath,
						   double zoomFactor);

			ImageComponent(GameObject &gameObject,
				           std::string imagePath,
						   double zoomFactor,
						   std::pair<double,
						   double> positionRelativeToObject);
			void Init();
			void Draw();
			void UpdateQuad();
			inline std::string GetClassName() {
				return "ImageComponent";
			}
	};
}

#endif
