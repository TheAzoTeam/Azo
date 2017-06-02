#ifndef MENU_CODE_HPP
#define MENU_CODE_HPP

#include "code_component.hpp"
#include "audio_controller.hpp"

#include "log.h"
#include "game_globals.hpp"


#include <string>

namespace Azo {
	class MenuCode : public engine::CodeComponent {
		private:
			engine::AudioController *audio_controller;
		public:
			MenuCode();
			MenuCode(engine::GameObject &game_object);
			~MenuCode();
			void UpdateCode();
		private:
			void NextScene();
			void DisableSound();
			void FindAudioController();

	};
}

#endif