#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

#include "game_object.hpp"
#include "sprite.hpp"

#include "player_code.hpp"
#include "obstacle.hpp"

namespace Azo {

	enum class PlayerState {
		WALK,
		JUMP,
		SLIDE,
		DIE,
	};

	class Player : public engine::GameObject {
		private:
			engine::AnimationController * m_anim_controller;

			// Add new animations here.
			engine::Animation *m_walking;
			engine::Animation *m_jumping;
			engine::Animation *m_sliding;
			engine::Animation *m_dying;

			// Add new sprite vectors here.
			std::vector<engine::Sprite *> m_walking_animation_sprites;
			std::vector<engine::Sprite *> m_jumping_animation_sprites;
			std::vector<engine::Sprite *> m_sliding_animation_sprites;
			std::vector<engine::Sprite *> m_dying_animation_sprites;

			PlayerCode *m_player_code;
		public:
			const std::pair<double, double> M_ZERO_VECTOR = std::make_pair(0.0f, 0.0f);
			const double M_GRAVITY = 0.003f;
			const double M_JUMPING_SPEED = -1.0f; //Vertical speed should be negative, so the character goes up on canvas.
			const double M_WALKING_SPEED = 0.30f;

			PlayerState m_state;
			std::pair<double, double> m_speed;

			bool m_pushes_right_wall;
			bool m_pushes_left_wall;
			bool m_at_ceiling;
			bool m_on_ground;

		private:
			// Don't forget to create new components inside this method.
			void CreateComponents();

			// Add new methods to generate the sprite vectors here.
			void GenWalkingAnimation();
			void GenJumpingAnimation();
			void GenSlidingAnimation();
			void GenDyingAnimation();

			inline std::string GetClassName(){
				return "Player";
			}

		public:
			Player();
			Player(std::string name, std::pair<double, double> current_position);
	};
}

#endif