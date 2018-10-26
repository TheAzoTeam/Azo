/**
     * @file menu_code.cpp
     * @brief Purpose: Archive responsible for the operation of the ' menu '
     *
     * GPL 3.0 License
     * Copyright (c) 2017 Azo
     *
     * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
     */
#include "game.hpp"
#include "menu_code.hpp"

using namespace Azo;

/**
     * @brief function responsible for building menu
     *
     * Why: Used to build menu on the map
     *
	 * @param Gameobject that is the creation object of the ' menu '
     */
MenuCode::MenuCode(engine::GameObject *gameObject){
	this->gameObject = gameObject; // Variable responsible for game object.
	findAudioController();
	findAnimationController();
}
/**
     * @brief function responsible for finding animation controller
     *
     * Why: Used to control the animation of the game
     *
     * @return "void".
     */
void MenuCode::findAnimationController(){
	 mAnimationController = (gameObject->getAnimationController(typeid(engine::AnimationController)));
}

/**
     * @brief function responsible for finding audio controller
     *
     * Why: Used to control game audio
     *
     * @return "void".
     */
void MenuCode::findAudioController(){
	 mAudioController = (gameObject->getAudioController(typeid(engine::AudioController)));
}

/**
     * @brief function responsible for updating game states
     *
     * Why: Used so that the game can consistently respond to the player's inputs
     *
     * @return "void".
     */
void MenuCode::updateCode(){
	if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::ENTER)){

		switch (mCurrentButton) {
			case 1:
				mAudioController->stopAudio("menu_theme");
				engine::Game::instance.changeScene("level_one");
				break;
			case 2:
				engine::Game::instance.gameState = engine::GameState::EXIT; // Variable responsible for the state of game.
				break;
			case 3:
				if(mAudioController->getAudioState("menu_theme") == engine::AudioState::PLAYING){
					mAudioController->pauseAudio("menu_theme");
					mAnimationController->stopAnimation("sound_enabled_button");
					mAnimationController->startAnimation("sound_disabled_button");
				} else {
					mAudioController->playAudio("menu_theme");
					mAnimationController->startAnimation("sound_enabled_button");
					mAnimationController->stopAnimation("sound_disabled_button");
				}
				break;
			default:
				// Nothing to do, no button selected.
		}
	}
	changeOption();
}

/**
     * @brief function responsible for selecting game option
     *
     * Why: Used so that the user can select the options in the menu
     *
     * @return "void".
     */
void MenuCode::changeOption(){

	switch (mCurrentButton) {
		// Start Option.
		case 1:
			DEBUG("Start Button is selected.");

			mAnimationController->startAnimation("arrow_start");


			if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::RIGHT_ARROW)){
				mAnimationController->stopAnimation("arrow_start");

				mCurrentButton = 2;

			} else if (engine::Game::instance.inputManager.keyDownOnce(engine::Button::LEFT_ARROW)) {
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
			} else if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::LEFT_ARROW)){
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

			} else if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::LEFT_ARROW)){
				mAnimationController->stopAnimation("arrow_sound");

				mCurrentButton = 2;
			}
			break;
		default:
			// Nothing to do, no button defined.
	}
}
