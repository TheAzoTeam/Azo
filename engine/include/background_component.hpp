#ifndef BACKGROUND_COMPONENT_HPP
#define BACKGROUND_COMPONENT_HPP

#include "image_component.hpp"

namespace engine {
	class BackgroundComponent : public ImageComponent {
		public:
			BackgroundComponent();
			BackgroundComponent(GameObject &game_object, std::string image_path);
			bool Init();
	};
}

#endif