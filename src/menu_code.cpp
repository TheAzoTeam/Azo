#include "game.hpp"
#include "menu_code.hpp"

using namespace Azo;

MenuCode::MenuCode(engine::GameObject *gameObject){
	this->gameObject = gameObject;
	findAudioController();
	FindAnimationController();
}

void MenuCode::FindAnimationController(){
	 mAnimationController = (gameObject->getAnimationController(typeid(engine::AnimationController)));
}

void MenuCode::findAudioController(){
	 mAudioController = (gameObject->getAudioController(typeid(engine::AudioController)));
}

void MenuCode::updateCode(){
	if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::ENTER)){

		switch (mCurrentButton) {
			case 1:
				mAudioController->stopAudio("menu_theme");
				engine::Game::instance.changeScene("level_one");
				break;
			case 2:
				engine::Game::instance.gameState = engine::GameState::EXIT;
				break;
			case 3:

				if(mAudioController->getAudioState("menu_theme") == engine::AudioState::PLAYING){
					mAudioController->pauseAudio("menu_theme");
					mAnimationController->stopAnimation("sound_enabled_button");
					mAnimationController->startAnimation("sound_disabled_button");
				}else{
					mAudioController->playAudio("menu_theme");
					mAnimationController->startAnimation("sound_enabled_button");
					mAnimationController->stopAnimation("sound_disabled_button");
				}

				break;

		}
	}

	changeOption();
}

void MenuCode::changeOption(){

	switch (mCurrentButton) {
		// Start Option.
		case 1:
			DEBUG("Start Button is selected.");

			mAnimationController->startAnimation("arrow_start");


			if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::RIGHT_ARROW)){
				mAnimationController->stopAnimation("arrow_start");

				mCurrentButton = 2;

			}

			if (engine::Game::instance.inputManager.keyDownOnce(engine::Button::LEFT_ARROW)) {
				mAnimationController->stopAnimation("arrow_start");
				mCurrentButton = 3;
			}

			break;
		// Exit Option.
		case 2:
			DEBUG("Exit Button is selected.");


			mAnimationController->startAnimation("arrow_exit");

			if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::RIGHT_ARROW)){
				mAnimationController->stopAnimation("arrow_exit");

				mCurrentButton = 3;
			}

			if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::LEFT_ARROW)){
				mAnimationController->stopAnimation("arrow_exit");

				mCurrentButton = 1;
			}

			break;
		// Sound Option.
		case 3:
			DEBUG("Sound Button is selected.");

			mAnimationController->startAnimation("arrow_sound");

			if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::RIGHT_ARROW)){
				mAnimationController->stopAnimation("arrow_sound");

				// Go back to the first option.
				mCurrentButton = 1;

			}

			if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::LEFT_ARROW)){
				mAnimationController->stopAnimation("arrow_sound");

				mCurrentButton = 2;
			}

			break;
	}
}
