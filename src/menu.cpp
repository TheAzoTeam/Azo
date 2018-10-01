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

/**  * T11
     * @brief function responsible for creating menu scene
     *
     * Why: Because it is necessary for the player to have access to the game menu before it starts
     */
Menu::Menu(std::string name) {
	this->sceneName = name;
	createGameObjects();
}

/**  * T11
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

/**  * T11
     * @brief function responsible for creating game objects
     *
     * Why: Because it is necessary for the menu to have some elements in its interface
	 *
	 * @return "void".
     */
void Menu::createGameObjects() {
	DEBUG("Creating Menu GameObjects.");

	mMenu = new engine::GameObject("menu", std::make_pair(0, 0));
	createMenuComponents();

	this->addGameObject(*mMenu);
}

/**  * T11
     * @brief function responsible for creating game objects
     *
     * Why: Because it is necessary that the menu has some elements in its interfacece
	 *
	 * @return "void".
     */
void Menu::createMenuComponents() {

	mMenuTheme = new engine::AudioComponent(*mMenu, "audios/TemaGame.ogg", true, true);
	mAudioController = new engine::AudioController();

	mAudioController->addAudio("menu_theme", *mMenuTheme);
	mMenu->addComponent(*mAudioController);

	mAnimationController = new engine::AnimationController(*mMenu);

	generateButtonsAnimation();
	mStartButton = new engine::Animation(*mMenu,
					       				 "general_images/textos.png",
					       				 1.0f, // animationTime T14
					       				 mStartButtonSprites,
					       				 0, // startFrame T14
					       				 0, // endFrame T14
					       				 false, // loop T14
					       				 1, // zoomFactor T14
					       				 std::make_pair(205, 162)); // positionRelativeToObject T14

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

	mArrowSound->disableComponent();

	mAnimationController->addAnimation("arrow_sound", *mArrowSound);

	mMenu->addComponent(* mAnimationController);

	mBackground = new engine::BackgroundComponent(*mMenu, "backgrounds/menu.png");
	mMenu->addComponent(*mBackground);

	mCode = new MenuCode(mMenu);
	mMenu->addComponent(*mCode);
}

/**  * T11
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

/**  * T11
     * @brief function responsible for debugging
     *
     * Why: Because it is responsible for debugging the code
	 *
	 * @return "void".
     */
void Menu::shutdown() {
	DEBUG("Calling Menu::shutdown.");
}
