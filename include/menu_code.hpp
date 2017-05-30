#ifndef MENU_CODE_HPP
#define MENU_CODE_HPP

#include "code_component.hpp"
#include "log.h"
#include "game_globals.hpp"
#include <string>

namespace Azo {
	class MenuCode : public engine::CodeComponent {
		public:
			MenuCode();
			~MenuCode();
			bool UpdateCode();
			void SetGameObject(engine::GameObject &game_object);
	};
}

#endif