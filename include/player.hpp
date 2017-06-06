#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "game_object.hpp"
#include "player_code.hpp"
#include "sprite.hpp"

#include <vector>
#include <string>

namespace Azo {
	class Player : public engine::GameObject {
		private:
			engine::AnimationController * m_anim_controller;
			engine::Animation *m_walking;

			PlayerCode *m_player_code;
			std::vector<engine::Sprite *> m_walking_animation_sprites;

		private:
			void CreateComponents();
			void GenWalkingAnimation();
			inline std::string GetClassName(){
				return "Player";
			}
		public:
			Player();
			Player(std::string name, int x, int y);
	};
}

#endif