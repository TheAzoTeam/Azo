#ifndef CODE_COMPONENT_HPP
#define CODE_COMPONENT_HPP

#include "game.hpp"
#include "input_manager.hpp"

namespace engine {

	class CodeComponent : public Component {
		private:
			InputManager input_manager;

		public:
			CodeComponent(GameObject &game_object) : Component(game_object){}

			bool Init();

			bool Shutdown();

			bool UpdateCode();

	};
}

#endif
