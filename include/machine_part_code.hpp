#ifndef MACHINE_PART_CODE
#define MACHINE_PART_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class Obstacle;

	class MachinePartCode : public engine::CodeComponent {
		private:
			Obstacle *m_machine_part;
			engine::AudioController *m_audio_controller;
		public:
			MachinePartCode(Obstacle *machine_part);
			virtual ~MachinePartCode();
			void shutdown();
		private:
			void updateCode();
			void FindAudioController();
	};
}
#endif