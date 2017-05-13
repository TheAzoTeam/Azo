#ifndef CODE_COMPONENT_HPP
#define CODE_COMPONENT_HPP

#include "game_object.hpp"
#include "component.hpp"
#include "input_manager.hpp"
#include "game.hpp"
#include "timer.hpp"


namespace engine {

	class CodeComponent : public Component {
		protected:
			InputManager input_manager;
			bool jump = false;
			Timer timer;

		public:
			CodeComponent();

			CodeComponent(GameObject &game_object);

			bool Init();

			bool Shutdown();

			bool UpdateCode();
	};
}

#endif
