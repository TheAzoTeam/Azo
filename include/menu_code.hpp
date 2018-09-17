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
			MenuCode(engine::GameObject *gameObject);
		private:
			void updateCode();
			void findAudioController();
			void FindAnimationController();
			void changeOption();
	};
}

#endif
