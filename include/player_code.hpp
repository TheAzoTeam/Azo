#ifndef PLAYER_CODE_HPP
#define PLAYER_CODE_HPP

#include <typeinfo>
#include <typeindex>

#include "code_component.hpp"
#include "animation_controller.hpp"
#include "timer.hpp"
#include "floor.hpp"
#include "wall.hpp"


namespace Azo {

	enum class PlayerState {
		JUMPING,
		FALLING,
		RUNNING,
		NOT_RUNNING,
	};

	class PlayerCode : public engine::CodeComponent {
		private:
			engine::Timer timer;
			engine::AnimationController anim_controller;
			PlayerState state;

			void CheckCollisionWithFloor();
			void CheckCollisionWithWall();
			void Run();
			void CheckJump();
			void CheckSlide();
			void Gravity();

		public:
			PlayerCode();
			PlayerCode(engine::GameObject &game_object);
			void UpdateCode();
			void FindAnimationController();
	};

}

#endif
