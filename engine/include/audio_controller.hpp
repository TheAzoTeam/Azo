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
			void addAudio(std::string audioName, AudioComponent &audio);
			void playAudio(std::string audioName);
			void stopAudio(std::string audioName);
			void pauseAudio(std::string audioName);
			void stopAllAudios();
			AudioState getAudioState(std::string audioName);
			void Init();
			void Shutdown();
			void UpdateCode();

	};

}

#endif
