/**
 * @file image_component.hpp
 * @brief Purpose: Contains the components of the image component.
 * 
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 * 
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 * 
 * This file implements the main image component its declaration and state.
*/
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
			void init();
			void draw();
			void updateQuad();
			inline std::string getClassName() {
				return "ImageComponent";
			}
	};
}

#endif
