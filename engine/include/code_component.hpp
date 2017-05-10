#ifndef CODE_COMPONENT_HPP
#define CODE_COMPONENT_HPP

#include "game_object.hpp"
#include "component.hpp"
#include "input_manager.hpp"
#include "game.hpp"


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
