#include "player_code.hpp"
#include "game.hpp"
#include "player.hpp"

using namespace Azo;

PlayerCode::PlayerCode() {}

PlayerCode::~PlayerCode() {}

PlayerCode::PlayerCode(Player *player) {
	mPlayer = player;
	mPlayer->mState = PlayerState::WALK;
	mPlayer->mOnGround = true;
	FindAnimationController();
	FindAudioController();
}


void PlayerCode::FindAnimationController() {
	mAnimationController = (mPlayer->GetAnimationController(typeid(engine::AnimationController)));
}

void PlayerCode::FindAudioController() {
	mAudioController = (mPlayer->GetAudioController(typeid(engine::AudioController)));
}

void PlayerCode::Shutdown() {
	if (mAnimationController != NULL) {
		mAnimationController = NULL;
	}
}


void PlayerCode::UpdateCode() {
	switch (mPlayer->mState) {
		case PlayerState::WALK:

			mAnimationController->StartUniqueAnimation("walking");

			if (mPlayer->m_pushes_right_wall || mPlayer->m_pushes_left_wall){
				//DEBUG("Update code method. Player Speed in X: " << mPlayer->m_speed.first);
				mPlayer->m_speed.first = mPlayer->M_ZERO_VECTOR.first;
			} else {
				mPlayer->m_speed.first = mPlayer->M_WALKING_SPEED;
				//DEBUG("PLAYER SHOULD HAVE SPEED! PLAYER SPEED " << mPlayer->m_speed.first);
			}

			if (engine::Game::instance.input_manager.KeyState(engine::Button::W)) {
				//DEBUG("W pressed!");
				mPlayer->mState = PlayerState::JUMP;
				mPlayer->m_speed.second = mPlayer->M_JUMPING_SPEED; // Jumping speed.

			} else if (!mPlayer->mOnGround) {
				//DEBUG("Player isn't on ground. (WALK)");
				mPlayer->mState = PlayerState::JUMP;
			}

			if(engine::Game::instance.input_manager.KeyState(engine::Button::S)) {
				mPlayer->mState = PlayerState::SLIDE;
			}

			break;

		case PlayerState::JUMP:

			if (mPlayer->mOnGround) {
				mPlayer->mState = PlayerState::WALK;
			}

			mAnimationController->StartUniqueAnimation("jumping");

			mPlayer->m_speed.second += (mPlayer->M_GRAVITY * engine::Game::instance.GetTimer().GetDeltaTime());
			//DEBUG("UpdateCode method. Player Speed in Y: " << mPlayer->m_speed.second);

			if (mPlayer->m_pushes_right_wall) {
				mPlayer->m_speed.first = mPlayer->M_ZERO_VECTOR.first;
			} else {
				mPlayer->m_speed.first = mPlayer->M_WALKING_SPEED;         // Walking speed.
			}

			// if(mPlayer->m_pushes_left_wall){
			//      mPlayer->m_speed.first = mPlayer->M_ZERO_VECTOR.first;
			// }

			break;

		case PlayerState::SLIDE:
			mAnimationController->StartUniqueAnimation("sliding");

			if (mAnimationController->
				GetAnimationStatus("sliding") == engine::AnimationState::FINISHED) {
				mPlayer->mState = PlayerState::WALK;
				break;
			}

			mPlayer->m_speed.second += (mPlayer->M_GRAVITY * engine::Game::instance.GetTimer().GetDeltaTime());
			//DEBUG("Player speed: " << mPlayer->m_speed.second);

			if (mPlayer->m_pushes_right_wall) {
				mPlayer->m_speed.first = mPlayer->M_ZERO_VECTOR.first;
				//TODO(Roger): Change this state to DEATH.
				mPlayer->mState = PlayerState::WALK;
			}

			if (engine::Game::instance.input_manager.KeyState(engine::Button::W)) {
				mPlayer->mState = PlayerState::JUMP;
				mPlayer->m_speed.second = mPlayer->M_JUMPING_SPEED;
			}

			break;
		case PlayerState::DIE:
			mAnimationController->StartUniqueAnimation("dying");

			mAudioController->PlayAudio("lost");

			break;
		case PlayerState::END:
			if (mPlayer->m_collected_parts < mPlayer->M_TOTAL_PARTS) {
				mAnimationController->StartUniqueAnimation("losing");

				if (mAnimationController->GetAnimationStatus("losing") == engine::AnimationState::FINISHED) {
					mAudioController->PlayAudio("lost");
				}
			} else {
				mAnimationController->StartUniqueAnimation("victory");
				mAudioController->PlayAudio("victory");
			}

			break;
	}
}
