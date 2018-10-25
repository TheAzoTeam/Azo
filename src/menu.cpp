/**
     * @file menu.cpp
	 * @brief Purpose: Responsible for the Map menu screen
     *
     * GPL 3.0 License
     * Copyright (c) 2017 Azo
     *
     * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
     */
#include "menu.hpp"

using namespace Azo;

/**
     * @brief function responsible for creating menu scene
     *
     * Why: Because it is necessary for the player to have access to the game menu before it starts
     */
Menu::Menu(std::string name) {
	ASSERT(name != "", "The name can't be empty."); //T17
	this->sceneName = name;
	createGameObjects();
}

/**
     * @brief function responsible for restarting the game
     *
     * Why: Because it is necessary that the player can restart the game
	 *
	 * @return "void".
     */
void Menu::restart(){
	gameObjectMap.clear();
	createGameObjects();
}

/**
     * @brief function responsible for creating game objects
     *
     * Why: Because it is necessary for the menu to have some elements in its interface
	 *
	 * @return "void".
     */
void Menu::createGameObjects() {
	DEBUG("Creating Menu GameObjects.");


	mMenu = new engine::GameObject("menu", std::make_pair(0, 0));
	ASSERT(mMenu != NULL, "The mMenu can't be null."); //T17

	createMenuComponents();

	this->addGameObject(*mMenu);
}

/**
     * @brief function responsible for creating game objects
     *
     * Why: Because it is necessary that the menu has some elements in its interfacece
	 *
	 * @return "void".
     */
void Menu::createMenuComponents() {


	mMenuTheme = new engine::AudioComponent(*mMenu, "audios/TemaGame.ogg", true, true);
    ASSERT(mMenuTheme != NULL, "The mMenuTheme can't be null."); //T17

	mAudioController = new engine::AudioController();
    ASSERT(mAudioController != NULL, "The mAudioController can't be null."); //T17

	mAudioController->addAudio("menu_theme", *mMenuTheme);
	mMenu->addComponent(*mAudioController);


	mAnimationController = new engine::AnimationController(*mMenu);
	ASSERT(mAnimationController != NULL, "The mAnimationController can't be null.");//T17

	generateButtonsAnimation();

	mStartButton = new engine::Animation(*mMenu,
					       				 "general_images/textos.png",
					       				 1.0f, // animationTime
					       				 mStartButtonSprites,
					       				 0, // startFrame
					       				 0, // endFrame
					       				 false, // loop
					       				 1, // zoomFactor
					       				 std::make_pair(205, 162)); // positionRelativeToObject

	ASSERT(mStartButton != NULL, "The mStartButton can't be null."); //T17


	mAnimationController->addAnimation("start_button", *mStartButton);


	mArrowStart = new engine::Animation(*mMenu,
					      				"general_images/textos.png",
					      				1.0f,
					      				mArrowSprites,
					      				0,
					      				0,
					      				false,
					      				1,
					      				std::make_pair(168, 162));
	ASSERT(mArrowStart != NULL, "The mArrowStart can't be null."); //T17

	mAnimationController->addAnimation("arrow_start", *mArrowStart);


	mExitButton = new engine::Animation(*mMenu,
					      				"general_images/textos.png",
					      				1.0f,
					      				mExitButtonSprites,
					      				0,
					      				0,
					      				false,
										1,
					      				std::make_pair(551, 162));
	ASSERT(mExitButton != NULL, "The mExitButton can't be null."); //T17

	mAnimationController->addAnimation("exit_button", *mExitButton);


	mArrowExit = new engine::Animation(*mMenu,
					     				"general_images/textos.png",
					     				1.0f,
					     				mArrowSprites,
					     				0,
					     				0,
					     				false,
					     				1,
					     				std::make_pair(514, 162));
	ASSERT(mArrowExit != NULL, "The mArrowExit can't be null.");//T17

	mArrowExit->disableComponent();

	mAnimationController->addAnimation("arrow_exit", *mArrowExit);


	mSoundEnabledButton = new engine::Animation(*mMenu,
						      				   "general_images/textos.png",
						      				   1.0f,
						      				   mSoundEnabledButtonSprites,
						      				   0,
						      				   0,
						      				   false,
						      				   1,
						      				   std::make_pair(708, 40));
	//T17
	ASSERT(mSoundEnabledButton != NULL, "The mSoundEnabledButton can't be null.");

	mAnimationController->addAnimation("sound_enabled_button", *mSoundEnabledButton);


	mSoundDisabledButton = new engine::Animation(*mMenu,
												 "general_images/textos.png",
												 1.0f,
												 mSoundDisabledButtonSprites,
												 0,
												 0,
												 false,
												 1,
												 std::make_pair(708, 40));
	//T17
	ASSERT(mSoundDisabledButton != NULL, "The mSoundDisabledButton can't be null.");

	mSoundDisabledButton->disableComponent();

	mAnimationController->addAnimation("sound_disabled_button", *mSoundDisabledButton);


	mArrowSound = new engine::Animation(*mMenu,
					      				"general_images/textos.png",
					      				1.0f,
					      				mArrowSprites,
					      				0,
					      				0,
					      				false,
					      				1,
					      				std::make_pair(676, 40));
	//T17
	ASSERT(mArrowSound!= NULL, "The mArrowSound can't be null.");

	mArrowSound->disableComponent();

	mAnimationController->addAnimation("arrow_sound", *mArrowSound);

	mMenu->addComponent(* mAnimationController);


	mBackground = new engine::BackgroundComponent(*mMenu, "backgrounds/menu.png");
	ASSERT(mBackground!= NULL, "The mBackground can't be null.");//T17

	mMenu->addComponent(*mBackground);


	mCode = new MenuCode(mMenu);
	ASSERT(mCode != NULL, "The mCode can't be null."); //T17

	mMenu->addComponent(*mCode);
}

/**
     * @brief function responsible for generating button animations
     *
     * Porque: For aesthetic purposes
	 *
	 * @return "void"
     */
void Menu::generateButtonsAnimation() {
	 mStartButtonSprites.push_back(new engine::Sprite());

	/*
		Set the animation sprites coordinates (x, y)
		and its Width and Height based on its coordinates
		spriteWidth = (width - spriteX) and spriteHeight = (Height - spriteY)
	*/

	 mStartButtonSprites[0]->spriteX = 43;
	 mStartButtonSprites[0]->spriteY = 452;
	 mStartButtonSprites[0]->spriteWidth = 161 - 43;
	 mStartButtonSprites[0]->spriteHeight = 478 - 452;

	mExitButtonSprites.push_back(new engine::Sprite());

	mExitButtonSprites[0]->spriteX = 207;
	mExitButtonSprites[0]->spriteY = 413;
	mExitButtonSprites[0]->spriteWidth = 280 - 207;
	mExitButtonSprites[0]->spriteHeight = 441 - 413;

	mSoundEnabledButtonSprites.push_back(new engine::Sprite());

	mSoundEnabledButtonSprites[0]->spriteX = 660;
	mSoundEnabledButtonSprites[0]->spriteY = 46;
	mSoundEnabledButtonSprites[0]->spriteWidth = 702 - 660;
	mSoundEnabledButtonSprites[0]->spriteHeight = 77 - 46;

	mSoundDisabledButtonSprites.push_back(new engine::Sprite());

	mSoundDisabledButtonSprites[0]->spriteX = 608;
	mSoundDisabledButtonSprites[0]->spriteY = 46;
	mSoundDisabledButtonSprites[0]->spriteWidth = 646 - 608;
	mSoundDisabledButtonSprites[0]->spriteHeight = 77 - 46;

	mArrowSprites.push_back(new engine::Sprite());

	mArrowSprites[0]->spriteX = 582;
	mArrowSprites[0]->spriteY = 433;
	mArrowSprites[0]->spriteWidth = 598 - 582;
	mArrowSprites[0]->spriteHeight = 459 - 433;
}

/**
     * @brief function responsible for debugging
     *
     * Why: Because it is responsible for debugging the code
	 *
	 * @return "void".
     */
void Menu::shutdown() {
	DEBUG("Calling Menu::shutdown.");
}
