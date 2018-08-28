#ifndef MENU_CODE
#define MENU_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class MenuCode : public engine::CodeComponent {
		private:
			engine::AudioController * mAudioController;
			engine::AnimationController * mAnimationController;
			int m_current_button = 1;
		public:
			MenuCode(engine::GameObject *game_object);
		private:
			void UpdateCode();
			void FindAudioController();
			void FindAnimationController();
			void ChangeOption();
	};
}

#endif