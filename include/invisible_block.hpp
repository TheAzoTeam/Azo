#ifndef INVISIBLE_BLOCK
#define INVISIBLE_BLOCK

#include "game_object.hpp"

namespace Azo {
	class InvisibleBlock : public engine::GameObject {
		//TODO(Roger): Remove this image.
		private:
			engine::ImageComponent *m_image;
		public:
			std::pair<double, double> mPositionRelativeToParent;
		public:
			InvisibleBlock();
			virtual ~InvisibleBlock();
			InvisibleBlock(std::string name, std::pair<double, double> positionRelativeToParent,
				       std::pair<double, double> size);
			void shutDown();
			inline std::string getClassName(){
				return "InvisibleBlock";
			}
	};
}

#endif
