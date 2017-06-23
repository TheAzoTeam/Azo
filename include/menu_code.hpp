#ifndef MENU_CODE
#define MENU_CODE

#include "code_component.hpp"

namespace Azo {
	class MenuCode : public engine::CodeComponent {
		public:
			MenuCode(engine::GameObject *game_object);
		private:
			void UpdateCode();
	};
}

#endif