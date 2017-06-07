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
			engine::Animation *m_jumping;


			PlayerCode *m_player_code;
			std::vector<engine::Sprite *> m_walking_animation_sprites;
			std::vector<engine::Sprite *> m_jumping_animation_sprites;

		private:
			void CreateComponents();
			void GenWalkingAnimation();
			void GenJumpingAnimation();
			inline std::string GetClassName(){
				return "Player";
			}
		public:
			Player();
			Player(std::string name, int x, int y);
	};
}

#endif