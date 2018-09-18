#ifndef MENU
#define MENU

#include "scene.hpp"
#include "menu_code.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class Menu : public engine::Scene {
		private:
			engine::GameObject *mMenu;

			engine::AnimationController *mAnimationController;

			engine::Animation *mStartButton;
			engine::Animation *mExitButton;
			engine::Animation *mSoundEnabledButton;
			engine::Animation *mSoundDisabledButton;

			engine::Animation *mArrowStart;
			engine::Animation *mArrowExit;
			engine::Animation *mArrowSound;

			std::vector<engine::Sprite *> mStartButtonSprites;
			std::vector<engine::Sprite *> mExitButtonSprites;
			std::vector<engine::Sprite *> mSoundEnabledButtonSprites;
			std::vector<engine::Sprite *> mSoundDisabledButtonSprites;

			std::vector<engine::Sprite *> mArrowSprites;

			engine::BackgroundComponent *mBackground;
			MenuCode *mCode;
			engine::AudioController *mAudioController;
			engine::AudioComponent *mMenuTheme;

		public:
			Menu();
			Menu(std::string name);
			void restart();
			void shutdown();
			
		private:
			void createGameObjects();
			void createMenuComponents();
			void generateButtonsAnimation();

	};
}

#endif