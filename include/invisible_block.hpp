#ifndef INVISIBLE_BLOCK
#define INVISIBLE_BLOCK

#include "game_object.hpp"

namespace Azo {
	class InvisibleBlock : public engine::GameObject {
		//TODO(Roger): Remove this image.
		private:
			engine::ImageComponent *m_image;
		public:
			std::pair<double, double> m_position_relative_to_parent;
		public:
			InvisibleBlock();
			//TODO(Roger): Remove this name attribute.
			InvisibleBlock(std::pair<double, double> position_relative_to_parent,
				       std::pair<double, double> size);
			inline std::string GetClassName(){
				return "InvisibleBlock";
			}
	};
}

#endif