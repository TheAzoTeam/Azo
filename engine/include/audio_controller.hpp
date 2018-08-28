#ifndef AUDIO_CONTROLLER_HPP
#define AUDIO_CONTROLLER_HPP

#include "audio_component.hpp"
#include "log.h"

#include <map>
#include <iostream>

namespace engine {

	class AudioController : public AudioComponent {
		private:
			std::map <std::string, AudioComponent *> audio_map;
		public:
			AudioController();
			virtual ~AudioController();
			AudioController(GameObject &gameObject);
			void AddAudio(std::string audio_name, AudioComponent &audio);
			void PlayAudio(std::string audio_name);
			void stopAudio(std::string audio_name);
			void PauseAudio(std::string audio_name);
			void stopAllAudios();
			AudioState getAudioState(std::string audio_name);
			void Init();
			void Shutdown();
			void updateCode();

	};

}

#endif
