#ifndef AUDIO_COMPONENT_HPP
#define AUDIO_COMPONENT_HPP

#include <string>

#include "sdl2include.h"
#include "component.hpp"
#include "log.h"

namespace engine {

	enum class AudioState {
		PLAYING,
		PAUSED,
		STOPPED
	};
	
	class AudioComponent : public Component {
	private:
		std::string audioPath;
		bool isMusic;
		bool playOnStart;

		Mix_Music * music;
		Mix_Chunk * sound;

	public:
		AudioState audio_state;
		AudioComponent();
		virtual ~AudioComponent();
		AudioComponent(GameObject & gameObject, std::string path, bool isMusic, bool playOnStart);
		void init();
		void shutdown();
		void updateCode();
		void play(int loops = -1, int channel = -1);
		void stop(int channel = -1);
		void pause(int channel = -1);
		inline bool getIsMusic(){ return isMusic; }
	};

}

#endif
