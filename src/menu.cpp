#include "menu.hpp"

using namespace Azo;

Menu::Menu(std::string name){
	this->sceneName = name;
	createGameObjects();
}

void Menu::restart(){
	gameObjectMap.clear();
	createGameObjects();
}

void Menu::createGameObjects(){
	DEBUG("Creating Menu GameObjects.");

	const std::string OBJECT_NAME = "menu";
	const auto CURRENT_POSITION = std::pair<int, int>(0, 0);

	mMenu = new engine::GameObject(OBJECT_NAME, CURRENT_POSITION);
	createMenuComponents();

	this->AddGameObject(*mMenu);
}

void Menu::createMenuComponents(){

	const std::string AUDIO_PATH = "audios/TemaGame.ogg";
	const bool IS_MUSIC = true;
	const bool PLAY_ON_START = true;

	mMenuTheme = new engine::AudioComponent(*mMenu, AUDIO_PATH, IS_MUSIC, PLAY_ON_START);
	mAudioController = new engine::AudioController();

	const std::string AUDIO_NAME = "menu_theme";
	mAudioController->addAudio(AUDIO_NAME, *mMenuTheme);
	mMenu->addComponent(*mAudioController);

	mAnimationController = new engine::AnimationController(*mMenu);

	genButtonsAnimation();

	const std::string START_BUTTOM_IMAGE_PATH = "general_images/textos.png";
	const float START_BUTTOM_ANIMATION_TIME = 1.0f;
	const int START_BUTTON_START_FRAME = 0;
	const int START_BUTTON_END_FRAME = 0;
	const bool START_BUTTOM_LOOP = false;
	const double START_BUTTOM_ZOOM_FACTOR = 1;
	const auto START_BUTTOM_RELATIVE_POSITION = std::pair<int, int>(205, 162);
	mStartButton = new engine::Animation(*mMenu,
					       START_BUTTOM_IMAGE_PATH,
					       START_BUTTOM_ANIMATION_TIME,
					       mStartButtonSprites,
					       START_BUTTON_START_FRAME,
					       START_BUTTON_END_FRAME,
					       START_BUTTOM_LOOP,
					       START_BUTTOM_ZOOM_FACTOR,
					       std::make_pair(205, 162));

	const std::string START_BUTTOM_NAME = "start_button";
	mAnimationController->addAnimation(START_BUTTOM_NAME, *mStartButton);

	const std::string ARROW_START_IMAGE_PATH = "general_images/textos.png";
	const float ARROW_START_ANIMATION_TIME = 1.0f;
	const int ARROW_START_START_FRAME = 0;
	const int ARROW_START_END_FRAME = 0;
	const bool ARROW_START_LOOP = false;
	const double ARROW_START_ZOOM_FACTOR = 1;
	const auto ARROW_START_RELATIVE_POSITION = std::pair<int, int>(168, 162);
	mArrowStart = new engine::Animation(*mMenu,
					      ARROW_START_IMAGE_PATH,
					      ARROW_START_ANIMATION_TIME,
					      mArrowSprites,
					      ARROW_START_START_FRAME,
					      ARROW_START_END_FRAME,
					      ARROW_START_LOOP,
					      ARROW_START_ZOOM_FACTOR,
					      ARROW_START_RELATIVE_POSITION);

	const std::string ARROW_START_NAME = "arrow_start";
	mAnimationController->addAnimation(ARROW_START_NAME, *mArrowStart);

	const std::string EXIT_BUTTOM_IMAGE_PATH = "general_images/textos.png";
	const float EXIT_BUTTOM_ANIMATION_TIME = 1.0f;
	const int EXIT_BUTTON_START_FRAME = 0;
	const int EXIT_BUTTON_END_FRAME = 0;
	const bool EXIT_BUTTOM_LOOP = false;
	const double EXIT_BUTTOM_ZOOM_FACTOR = 1;
	const auto EXIT_BUTTOM_RELATIVE_POSITION = std::pair<int, int>(551, 162);
	mExitButton = new engine::Animation(*mMenu,
					      EXIT_BUTTOM_IMAGE_PATH,
					      EXIT_BUTTOM_ANIMATION_TIME,
					      mExitButtonSprites,
					      EXIT_BUTTON_START_FRAME,
					      EXIT_BUTTON_END_FRAME,
					      EXIT_BUTTOM_LOOP,
					      EXIT_BUTTOM_ZOOM_FACTOR,
					      EXIT_BUTTOM_RELATIVE_POSITION);

	const std::string EXIT_BUTTOM_NAME = "exit_button";
	mAnimationController->addAnimation(EXIT_BUTTOM_NAME, *mExitButton);

	const std::string ARROW_EXIT_IMAGE_PATH = "general_images/textos.png";
	const float ARROW_EXIT_ANIMATION_TIME = 1.0f;
	const int ARROW_EXIT_START_FRAME = 0;
	const int ARROW_EXIT_END_FRAME = 0;
	const bool ARROW_EXIT_LOOP = false;
	const double ARROW_EXIT_ZOOM_FACTOR = 1;
	const auto ARROW_EXIT_RELATIVE_POSITION = std::pair<int, int>(514, 162);
	mArrowExit = new engine::Animation(*mMenu,
					     ARROW_EXIT_IMAGE_PATH,
					     ARROW_EXIT_ANIMATION_TIME,
					     mArrowSprites,
					     ARROW_EXIT_START_FRAME,
					     ARROW_EXIT_END_FRAME,
					     ARROW_EXIT_LOOP,
					     ARROW_EXIT_ZOOM_FACTOR,
					     ARROW_EXIT_RELATIVE_POSITION);

	mArrowExit->disableComponent();

	const std::string ARROW_EXIT_NAME = "arrow_exit";
	mAnimationController->addAnimation(ARROW_EXIT_NAME, *mArrowExit);

	const std::string ENABLE_BUTTOM_IMAGE_PATH = "general_images/textos.png";
	const float ENABLE_BUTTOM_ANIMATION_TIME = 1.0f;
	const int ENABLE_BUTTOM_START_FRAME = 0;
	const int ENABLE_BUTTOM_END_FRAME = 0;
	const bool ENABLE_BUTTOM_LOOP = false;
	const double ENABLE_BUTTOM_ZOOM_FACTOR = 1;
	const auto ENABLE_BUTTOM_RELATIVE_POSITION = std::pair<int, int>(708, 40);
	mSoundEnableButton = new engine::Animation(*mMenu,
						      ENABLE_BUTTOM_IMAGE_PATH,
						      ENABLE_BUTTOM_ANIMATION_TIME,
						      mSoundEnabledButtonSprites,
						      ENABLE_BUTTOM_START_FRAME,
						      ENABLE_BUTTOM_END_FRAME,
						      ENABLE_BUTTOM_LOOP,
						      ENABLE_BUTTOM_ZOOM_FACTOR,
						      ENABLE_BUTTOM_RELATIVE_POSITION);

	const std::string ENABLE_BUTTOM_NAME = "sound_enabled_button";
	mAnimationController->addAnimation(ENABLE_BUTTOM_NAME, *mSoundEnableButton);

	const std::string DISABLED_BUTTOM_IMAGE_PATH = "general_images/textos.png";
	const float DISABLED_BUTTOM_ANIMATION_TIME = 1.0f;
	const int DISABLED_BUTTOM_START_FRAME = 0;
	const int DISABLED_BUTTOM_END_FRAME = 0;
	const bool DISABLED_BUTTOM_LOOP = false;
	const double DISABLED_BUTTOM_ZOOM_FACTOR = 1;
	const auto DISABLED_BUTTOM_RELATIVE_POSITION = std::pair<int, int>(708, 40);
	mSoundDisabledButton = new engine::Animation(*mMenu,
							DISABLED_BUTTOM_IMAGE_PATH,
							DISABLED_BUTTOM_ANIMATION_TIME,
							mSoundDisabledButtonSprites,
							DISABLED_BUTTOM_START_FRAME,
							DISABLED_BUTTOM_END_FRAME,
							DISABLED_BUTTOM_LOOP,
							DISABLED_BUTTOM_ZOOM_FACTOR,
							DISABLED_BUTTOM_RELATIVE_POSITION);

	mSoundDisabledButton->disableComponent();

	const std::string DISABLED_BUTTOM_NAME = "sound_disabled_button";
	mAnimationController->addAnimation(DISABLED_BUTTOM_NAME, *mSoundDisabledButton);

	const std::string ARROW_SOUND_IMAGE_PATH = "general_images/textos.png";
	const float ARROW_SOUND_ANIMATION_TIME = 1.0f;
	const int ARROW_SOUND_START_FRAME = 0;
	const int ARROW_SOUND_END_FRAME = 0;
	const bool ARROW_SOUND_LOOP = false;
	const double ARROW_SOUND_ZOOM_FACTOR = 1;
	const auto ARROW_SOUND_RELATIVE_POSITION = std::pair<int, int>(676, 40);
	mArrowSound = new engine::Animation(*mMenu,
					      ARROW_SOUND_IMAGE_PATH,
					      ARROW_SOUND_ANIMATION_TIME,
					      mArrowSprites,
					      ARROW_SOUND_START_FRAME,
					      ARROW_SOUND_END_FRAME,
					      ARROW_SOUND_LOOP,
					      ARROW_SOUND_ZOOM_FACTOR,
					      ARROW_SOUND_RELATIVE_POSITION);

	mArrowSound->disableComponent();

	const std::string ARROW_SOUND_NAME = "arrow_sound";
	mAnimationController->addAnimation(ARROW_SOUND_NAME, *mArrowSound);

	mMenu->addComponent(* mAnimationController);

	const std::string MENU_IMAGE_PATH = "backgrounds/menu.png";
	mBackground = new engine::BackgroundComponent(*mMenu, MENU_IMAGE_PATH);
	mMenu->addComponent(*mBackground);

	mCode = new MenuCode(mMenu);
	mMenu->addComponent(*mCode);
}

void Menu::genButtonsAnimation(){
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


void Menu::shutdown(){
	DEBUG("Calling Menu::shutdown.");
}