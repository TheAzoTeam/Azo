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
			void UpdatePhysics();
			void FindAnimationController();
			bool HasGround(double *ground_y);
			bool HasCeiling(double *ground_y);
			bool HasWallOnRight(double *wall_x);
			bool HasWallOnLeft(double *wall_x);
		public:
			PlayerCode();
			PlayerCode(Player *player);
	};
}

#endif