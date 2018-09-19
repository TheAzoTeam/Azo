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
	findAudioController();
}



void PlayerCode::FindAnimationController(){
	 mAnimationController = (mPlayer->getAnimationController(typeid(engine::AnimationController)));
}

void PlayerCode::findAudioController(){
	 mAudioController = (mPlayer->getAudioController(typeid(engine::AudioController)));
}

void PlayerCode::shutdown(){
	if( mAnimationController != NULL){
		 mAnimationController = NULL;

	}
}


void PlayerCode::updateCode(){
	switch(mPlayer->mState){
		case PlayerState::WALK:

			mAnimationController->startUniqueAnimation("walking");

			if(mPlayer->mPushesRightWall || mPlayer->mPushesLeftWall){
				//DEBUG("Update code method. Player Speed in X: " << mPlayer->mSpeed.first);
				mPlayer->mSpeed.first = mPlayer->M_ZERO_VECTOR.first;
			}else{
				mPlayer->mSpeed.first = mPlayer->M_WALKING_SPEED;
				//DEBUG("PLAYER SHOULD HAVE SPEED! PLAYER SPEED " << mPlayer->mSpeed.first);
			}

			if(engine::Game::instance.inputManager.keyState(engine::Button::W)){
				//DEBUG("W pressed!");
				mPlayer->mState = PlayerState::JUMP;
				mPlayer->mSpeed.second = mPlayer->M_JUMPING_SPEED; // Jumping speed.

			}else if(!mPlayer->mOnGround){
				//DEBUG("Player isn't on ground. (WALK)");
				mPlayer->mState = PlayerState::JUMP;
			}

			if(engine::Game::instance.inputManager.keyState(engine::Button::S)){
				mPlayer->mState = PlayerState::SLIDE;
			}

			break;

		case PlayerState::JUMP:

			if(mPlayer->mOnGround){
				mPlayer->mState = PlayerState::WALK;
			}

			mAnimationController->startUniqueAnimation("jumping");

			mPlayer->mSpeed.second += (mPlayer->M_GRAVITY * engine::Game::instance.getTimer().getDeltaTime());
			//DEBUG("UpdateCode method. Player Speed in Y: " << mPlayer->m_speed.second);

			if(mPlayer->mPushesRightWall){
				mPlayer->mSpeed.first = mPlayer->M_ZERO_VECTOR.first;
			}else{
				mPlayer->mSpeed.first = mPlayer->M_WALKING_SPEED;         // Walking speed.
			}

			// if(mPlayer->mPushesLeftWall){
			//      mPlayer->mSpeed.first = mPlayer->M_ZERO_VECTOR.first;
			// }

			break;

		case PlayerState::SLIDE:
			mAnimationController->startUniqueAnimation("sliding");

			if(mAnimationController->getAnimationStatus("sliding") == engine::AnimationState::FINISHED){
				mPlayer->mState = PlayerState::WALK;
				break;
			}

			mPlayer->mSpeed.second += (mPlayer->M_GRAVITY * engine::Game::instance.getTimer().getDeltaTime());
			//DEBUG("Player speed: " << mPlayer->mSpeed.second);

			if(mPlayer->mPushesRightWall){
				mPlayer->mSpeed.first = mPlayer->M_ZERO_VECTOR.first;
				//TODO(Roger): Change this state to DEATH.
				mPlayer->mState = PlayerState::WALK;
			}

			if(engine::Game::instance.inputManager.keyState(engine::Button::W)){
				mPlayer->mState = PlayerState::JUMP;
				mPlayer->mSpeed.second = mPlayer->M_JUMPING_SPEED;
			}

			break;
		case PlayerState::DIE:
			mAnimationController->startUniqueAnimation("dying");

			mAudioController->playAudio("lost");

			break;
		case PlayerState::END:
			if(mPlayer->mCollectedParts < mPlayer->M_TOTAL_PARTS){
				mAnimationController->startUniqueAnimation("losing");

				if(mAnimationController->getAnimationStatus("losing") == engine::AnimationState::FINISHED){
					mAudioController->playAudio("lost");
				}
			}else{
				mAnimationController->startUniqueAnimation("victory");
				mAudioController->playAudio("victory");
			}

			break;
	}
}
