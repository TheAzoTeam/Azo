#ifndef PLAYER_CODE_HPP
#define PLAYER_CODE_HPP

#include <typeinfo>
#include <typeindex>

#include "code_component.hpp"
#include "animation_controller.hpp"
#include "timer.hpp"


namespace Azo {

	enum class PlayerState {
		JUMPING,
		FALLING,
		RUNNING,
	};

	class PlayerCode : public engine::CodeComponent {
		private:
			bool jumping = false;
			bool falling = false;
			engine::Timer timer;
			engine::AnimationController anim_controller;
			PlayerState state;

			void ResolveCollision();

		public:
			PlayerCode();
			PlayerCode(engine::GameObject &game_object);
			bool UpdateCode();
			void SetGameObject(engine::GameObject &game_object);
			void FindAnimationController();
	};

}

#endif
