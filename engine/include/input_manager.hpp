#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "sdl2include.h"

#include <string>
#include <list>

namespace engine {

	enum Button {
		W = SDL_SCANCODE_W,
		S = SDL_SCANCODE_S,
		D = SDL_SCANCODE_D,
		A = SDL_SCANCODE_A,
		ENTER = SDL_SCANCODE_RETURN,
		SPACE = SDL_SCANCODE_SPACE,
		BACKSPACE = SDL_SCANCODE_BACKSPACE,
		LEFT_ARROW = SDL_SCANCODE_LEFT,
		RIGHT_ARROW = SDL_SCANCODE_RIGHT
	};

	class InputManager {
		private:
			unsigned int mLastEventType;
			std::list<SDL_Event> mEventList;
			const Uint8 *keyboardStates;
		public:
			InputManager();
			~InputManager();
			void update(SDL_Event _event);
			bool keyDown(Button button);
			bool keyDownOnce(Button button);
			bool keyState(Button button);
			void clear();

		private:
	};
}

#endif
