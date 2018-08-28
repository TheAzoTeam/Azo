#ifndef MENU_CODE
#define MENU_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class MenuCode : public engine::CodeComponent {
		private:
			engine::AudioController *m_audio_controller;
			engine::AnimationController *m_animation_controller;
			int m_current_button = 1;
		public:
			MenuCode(engine::GameObject *game_object);
		private:
			void updateCode();
			void findAudioController();
			void FindAnimationController();
			void changeOption();
	};
}

#endif