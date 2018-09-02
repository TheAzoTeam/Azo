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
			std::string audio_path;
			bool is_music;
			bool play_on_start;

			Mix_Music * music;
			Mix_Chunk * sound;

		public:
			AudioState audioState;

			AudioComponent();

			virtual ~AudioComponent();


			AudioComponent(GameObject & gameObject, std::string path, bool is_music, bool play_on_start);

			void Init();

			void Shutdown();

			void UpdateCode();

			void play(int loops = -1, int channel = -1);

			void stop(int channel = -1);

			void pause(int channel = -1);

			inline bool GetIsMusic(){
				return is_music;
			}
	};

}

#endif
