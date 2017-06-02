#ifndef DISABLE_SOUND_CODE_HPP
#define DISABLE_SOUND_CODE_HPP

#include "code_component.hpp"

namespace Azo {

	class DisableSoundCode : public engine::CodeComponent {
		private:
			engine::AudioController *audio_controller;
			void FindAudioController();
		public:
			DisableSoundCode();
			DisableSoundCode(engine::GameObject &game_object);
			void UpdateCode();

	};
}

#endif