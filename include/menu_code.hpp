#ifndef MENU_CODE
#define MENU_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class MenuCode : public engine::CodeComponent {
		private:
			engine::AudioController *mAudioController;
			engine::AnimationController *mAnimationController;
			int mCurrentButton = 1;
		public:
			MenuCode(engine::GameObject *gameObject);
		private:
			void UpdateCode();
			void FindAudioController();
			void FindAnimationController();
			void ChangeOption();
	};
}

#endif
