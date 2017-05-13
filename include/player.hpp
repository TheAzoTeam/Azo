#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "game_object.hpp"
#include "animation.hpp"
#include "player_code.hpp"
#include "animation_controller.hpp"
#include <string>

namespace Azo {
	class Player : public engine::GameObject {
		public:
			engine::AnimationController player_animation_controller;
		private:
			engine::Animation walking_animation;
			engine::Animation walking_backwards_animation;
			PlayerCode player_code;
		public:
			Player();
			Player(std::string player_name);
			void SetAnimations(Player &player);
			void SetCode(Player &player);
	};
}

#endif