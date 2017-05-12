#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "sdl2include.h"

namespace engine {

	class InputManager {
		private:
			const Uint8 *keyboard_states;
		public:
			InputManager();

			~InputManager();

			bool KeyDown(SDL_Scancode scan_code);

			void Update();
	};
}

#endif