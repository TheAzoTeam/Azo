#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "sdl2include.h"

#include <string>
#include <list>

namespace engine {

	enum Button {
		W = SDL_SCANCODE_W,
		S = SDL_SCANCODE_S,
		ENTER = SDL_SCANCODE_RETURN,
		SPACE = SDL_SCANCODE_SPACE
	};

	class InputManager {
		private:
			unsigned int last_event_type;
			std::list<SDL_Event> event_list;
		public:
			InputManager();

			~InputManager();

			void Update(SDL_Event _event);

			bool KeyDown(Button button);
			bool KeyDownOnce(Button button);

			void Clear();

		private:
	};
}

#endif