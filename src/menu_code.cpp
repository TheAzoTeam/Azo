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
	if(engine::Game::instance.input_manager.keyDownOnce(engine::Button::ENTER)){

		switch(m_current_button){
			case 1:
				mAudioController->stopAudio("menu_theme");
				engine::Game::instance.ChangeScene("level_one");
				break;
			case 2:
				engine::Game::instance.game_state = engine::GameState::EXIT;
				break;
			case 3:

				if(mAudioController->getAudioState("menu_theme") == engine::AudioState::PLAYING){
					mAudioController->PauseAudio("menu_theme");
					mAnimationController->stopAnimation("sound_enabled_button");
					mAnimationController->startAnimation("sound_disabled_button");
				}else{
					mAudioController->PlayAudio("menu_theme");
					mAnimationController->startAnimation("sound_enabled_button");
					mAnimationController->stopAnimation("sound_disabled_button");
				}

				break;

		}
	}

	changeOption();
}

void MenuCode::changeOption(){

	switch(m_current_button){
		// Start Option.
		case 1:
			DEBUG("Start Button is selected.");

			mAnimationController->startAnimation("arrow_start");


			if(engine::Game::instance.input_manager.keyDownOnce(engine::Button::RIGHT_ARROW)){
				mAnimationController->stopAnimation("arrow_start");

				m_current_button = 2;

			}

			if(engine::Game::instance.input_manager.keyDownOnce(engine::Button::LEFT_ARROW)){
				mAnimationController->stopAnimation("arrow_start");
				m_current_button = 3;
			}

			break;
		// Exit Option.
		case 2:
			DEBUG("Exit Button is selected.");


			mAnimationController->startAnimation("arrow_exit");

			if(engine::Game::instance.input_manager.keyDownOnce(engine::Button::RIGHT_ARROW)){
				mAnimationController->stopAnimation("arrow_exit");

				m_current_button = 3;
			}

			if(engine::Game::instance.input_manager.keyDownOnce(engine::Button::LEFT_ARROW)){
				mAnimationController->stopAnimation("arrow_exit");

				m_current_button = 1;
			}

			break;
		// Sound Option.
		case 3:
			DEBUG("Sound Button is selected.");

			mAnimationController->startAnimation("arrow_sound");

			if(engine::Game::instance.input_manager.keyDownOnce(engine::Button::RIGHT_ARROW)){
				mAnimationController->stopAnimation("arrow_sound");

				// Go back to the first option.
				m_current_button = 1;

			}

			if(engine::Game::instance.input_manager.keyDownOnce(engine::Button::LEFT_ARROW)){
				mAnimationController->stopAnimation("arrow_sound");

				m_current_button = 2;
			}

			break;
	}
}
