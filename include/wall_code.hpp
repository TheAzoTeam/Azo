#ifndef WALL_CODE_HPP
#define WALL_CODE_HPP

#include "code_component.hpp"

#include "code_component.hpp"

namespace Azo {
	class WallCode : public engine::CodeComponent {
		public:
			WallCode();
			WallCode(engine::GameObject &game_object);
			void UpdateCode();
	};
}

#endif

