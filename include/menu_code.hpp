/**
     * @file menu_code.hpp
	 * @brief Purpose: Declaration of the MenuCode class
     *
     * GPL 3.0 License
     * Copyright (c) 2017 Azo
     *
     * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
     */
#ifndef MENU_CODE
#define MENU_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	/** 
		 * @brief A Hitbox class.
		 * MenuCode class
		 *
		 * A more elaborate class description.
		 * Class responsible for creating the Menu features
		 */
	class MenuCode : public engine::CodeComponent {
		private:
			engine::AudioController *mAudioController; // Variable responsible for audio control
			engine::AnimationController *mAnimationController; // Variable responsible for animation control
			int mCurrentButton = 1; // Variable referring to the current button
		public:
			MenuCode(engine::GameObject *gameObject);
		private:
			void updateCode();
			void findAudioController();
			void findAnimationController();
			void changeOption();
	};
}

#endif
