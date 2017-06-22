#ifndef PLAYER_CODE
#define PLAYER_CODE

#include "code_component.hpp"
#include "animation_controller.hpp"

namespace Azo {
	class Player;

	class PlayerCode : public engine::CodeComponent {
		private:
			Player *m_player;
			engine::AnimationController *m_animation_controller;
			void UpdateCode();
			void FindAnimationController();
		public:
			PlayerCode();
			PlayerCode(engine::GameObject &game_object);
	};
}

#endif