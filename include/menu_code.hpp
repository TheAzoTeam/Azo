#ifndef MENU_CODE_HPP
#define MENU_CODE_HPP

#include "code_component.hpp"

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