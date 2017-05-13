#ifndef PLAYER_JUMPING_CODE_HPP
#define PLAYER_JUMPING_CODE_HPP

#include "code_component.hpp"
#include "timer.hpp"

namespace Azo {
	class PlayerJumpingCode : public engine::CodeComponent {
		private:
			bool jump = false;
			engine::Timer timer;

		public:
			PlayerJumpingCode();
			PlayerJumpingCode(engine::GameObject &game_object);
			bool UpdateCode();
			void SetGameObject(engine::GameObject & game_object);
	};
}

#endif