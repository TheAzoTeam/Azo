#ifndef INVISIBLE_BLOCK
#define INVISIBLE_BLOCK

#include "game_object.hpp"

namespace Azo {
	class InvisibleBlock : public engine::GameObject {
		public:
			std::pair<double, double> m_position_relative_to_parent;
		public:
			InvisibleBlock();
			InvisibleBlock(std::pair<double, double> position_relative_to_parent, std::pair<double, double> size);
	};
}

#endif