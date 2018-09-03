#include "game.hpp"
#include "menu_code.hpp"

using namespace Azo;

MenuCode::MenuCode(engine::GameObject *gameObject) {
	this->gameObject = gameObject;
	FindAudioController();
	FindAnimationController();
}

void MenuCode::FindAnimationController() {
	mAnimationController = (gameObject->GetAnimationController(typeid(engine::AnimationController)));
}

void MenuCode::FindAudioController() {
	mAudioController = (gameObject->GetAudioController(typeid(engine::AudioController)));
}

void MenuCode::UpdateCode() {
	if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)) {

		switch (mCurrentButton) {
			case 1:
				mAudioController->StopAudio("menu_theme");
				engine::Game::instance.ChangeScene("level_one");
				break;
			case 2:
				engine::Game::instance.game_state = engine::GameState::EXIT;
				break;
			case 3:

				if (mAudioController->GetAudioState("menu_theme") == engine::AudioState::PLAYING) {
					mAudioController->PauseAudio("menu_theme");
					mAnimationController->StopAnimation("sound_enabled_button");
					mAnimationController->StartAnimation("sound_disabled_button");
				} else {
					mAudioController->PlayAudio("menu_theme");
					mAnimationController->StartAnimation("sound_enabled_button");
					mAnimationController->StopAnimation("sound_disabled_button");
				}

				break;

		}
	}

	ChangeOption();
}

void MenuCode::ChangeOption() {

	switch (mCurrentButton) {
		// Start Option.
		case 1:
			DEBUG("Start Button is selected.");

			mAnimationController->StartAnimation("arrow_start");


			if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::RIGHT_ARROW)) {
				mAnimationController->StopAnimation("arrow_start");

				mCurrentButton = 2;

			}

			if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::LEFT_ARROW)) {
				mAnimationController->StopAnimation("arrow_start");
				mCurrentButton = 3;
			}

			break;
		// Exit Option.
		case 2:
			DEBUG("Exit Button is selected.");


			mAnimationController->StartAnimation("arrow_exit");

			if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::RIGHT_ARROW)) {
				mAnimationController->StopAnimation("arrow_exit");

				mCurrentButton = 3;
			}

			if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::LEFT_ARROW)) {
				mAnimationController->StopAnimation("arrow_exit");

				mCurrentButton = 1;
			}

			break;
		// Sound Option.
		case 3:
			DEBUG("Sound Button is selected.");

			mAnimationController->StartAnimation("arrow_sound");

			if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::RIGHT_ARROW)) {
				mAnimationController->StopAnimation("arrow_sound");

				// Go back to the first option.
				mCurrentButton = 1;

			}

			if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::LEFT_ARROW)) {
				mAnimationController->StopAnimation("arrow_sound");

				mCurrentButton = 2;
			}

			break;
	}
}
