#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "game_object.hpp"
#include "animation.hpp"

#include <string>

namespace Azo {
	class Player : public engine::GameObject {
		private:
			engine::Animation walking_animation;
		public:
			Player();
			Player(std::string player_name);
			void SetAnimations(Player &player);
	};
}

#endif