#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

#include "game_object.hpp"
#include "sprite.hpp"

#include "player_code.hpp"

namespace Azo {

	enum class PlayerState {
		WALK,
		JUMP,
	};

	class Player : public engine::GameObject {
		private:
			engine::AnimationController * m_anim_controller;
			engine::Animation *m_walking;
			engine::Animation *m_jumping;

			PlayerCode *m_player_code;

			std::vector<engine::Sprite *> m_walking_animation_sprites;
			std::vector<engine::Sprite *> m_jumping_animation_sprites;
		public:

			const std::pair<double, double> M_ZERO_VECTOR = std::make_pair(0.0f, 0.0f);
			const double M_GRAVITY = 0.003f;
			const double M_JUMPING_SPEED = -1.0f;                 //Vertical speed should be negative, so the character goes up on canvas.
			const double M_WALKING_SPEED = 0.30f;

			PlayerState m_state;
			std::pair<double, double> m_old_position;
			std::pair<double, double> m_speed;
			std::pair<double, double> m_old_speed;

			bool m_pushed_right_wall;
			bool m_pushes_right_wall;
			bool m_pushed_left_wall;
			bool m_pushes_left_wall;
			bool m_was_at_ceiling;
			bool m_at_ceiling;
			bool m_was_on_ground;
			bool m_on_ground;
			bool m_walking_right;

		private:
			void CreateComponents();
			void GenWalkingAnimation();
			void GenJumpingAnimation();
			inline std::string GetClassName(){
				return "Player";
			}
		public:
			Player();
			Player(std::string name, std::pair<double, double> current_position);
	};
}

#endif