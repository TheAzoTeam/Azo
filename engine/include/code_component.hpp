#ifndef CODE_COMPONENT_HPP
#define CODE_COMPONENT_HPP

#include "game_object.hpp"
#include "component.hpp"
#include "game.hpp"
#include "timer.hpp"


namespace engine {

	class CodeComponent : public Component {
		public:
			CodeComponent();

			CodeComponent(GameObject &game_object);

			void Init();

			void Shutdown();

			void updateCode();
	};
}

#endif
