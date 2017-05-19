#ifndef PLAYER_CODE_HPP
#define PLAYER_CODE_HPP

#include <typeinfo>
#include <typeindex>

#include "code_component.hpp"
#include "animation_controller.hpp"
#include "timer.hpp"


namespace Azo {

	class PlayerCode : public engine::CodeComponent {
		private:
			bool jump = false;
			engine::Timer timer;
			engine::AnimationController anim_controller;

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
