#ifndef AUDIO_CONTROLLER_HPP
#define AUDIO_CONTROLLER_HPP

#include "audio_component.hpp"
#include "log.h"

#include <map>
#include <iostream>

namespace engine {

	class AudioController : public AudioComponent {
		private:
			std::map <std::string, AudioComponent *> audioMap;
		public:
			AudioController();
			virtual ~AudioController();
			AudioController(GameObject &gameObject);
			void AddAudio(std::string audioName, AudioComponent &audio);
			void PlayAudio(std::string audioName);
			void StopAudio(std::string audioName);
			void PauseAudio(std::string audioName);
			void StopAllAudios();
			AudioState GetAudioState(std::string audioName);
			void Init();
			void Shutdown();
			void UpdateCode();

	};

}

#endif
