#ifndef FLOOR_CODE
#define FLOOR_CODE

#include "code_component.hpp"

namespace Azo {
	class FloorCode : public engine::CodeComponent {
		public:
			FloorCode();
			FloorCode(engine::GameObject &game_object);
			void UpdateCode();
	};
}

#endif