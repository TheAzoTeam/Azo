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
		END,
	};

	class Player : public engine::GameObject {
		private:
			engine::AnimationController *mAnimationController;
			engine::AudioController *mAudioController;

			// Add new audios here.
			engine::AudioComponent *mLost;
			engine::AudioComponent *mVictorySong;

			// Add new animations here.
			engine::Animation *mWalking;
			engine::Animation *mJumping;
			engine::Animation *mSliding;
			engine::Animation *mDying;
			engine::Animation *mLosing;
			engine::Animation *mVictory;

			// Add new sprite vectors here.
			std::vector<engine::Sprite *> mWalkingAnimationSprites;
			std::vector<engine::Sprite *> mJumpingAnimationSprites;
			std::vector<engine::Sprite *> mSlidingAnimationSprites;
			std::vector<engine::Sprite *> mDyingAnimationSprites;
			std::vector<engine::Sprite *> mLosingAnimationSprites;
			std::vector<engine::Sprite *> mVictoryAnimationSprites;

			PlayerCode *mPlayerCode;

		public:
			const std::pair<double, double> M_ZERO_VECTOR = std::make_pair(0.0f, 0.0f);
			const double M_GRAVITY = 0.003f;
			const double M_JUMPING_SPEED = -1.0f; //Vertical speed should be negative, so the character goes up on canvas.
			const double M_WALKING_SPEED = 4.8f;
			const int M_TOTAL_PARTS = 25;

			PlayerState mState;
			std::pair<double, double> mSpeed;

			bool mPushesRightWall;
			bool mPushesLeftWall;
			bool mAtCeiling;
			bool mOnGround;

			int mCollectedParts = 0;

		private:
			// Don't forget to create new components inside this method.
			void createComponents();

			// Add new methods to generate the sprite vectors here.
			void generateWalkingAnimation();
			void generateJumpingAnimation();
			void generateSlidingAnimation();
			void generateDyingAnimation();
			void generateLosingAnimation();
			void generateVictoryAnimation();

			inline std::string getClassName(){
				return "Player";
			}

		public:
			Player();
			Player(std::string name, std::pair<double, double> currentPosition);
			void shutdown();
	};
}

#endif