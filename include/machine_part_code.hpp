#ifndef MACHINE_PART_CODE
#define MACHINE_PART_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class Obstacle;

	class MachinePartCode : public engine::CodeComponent {
		private:
			Obstacle *m_machine_part;
			engine::AudioController *mAudioController;
		public:
			MachinePartCode(Obstacle *machine_part);
			virtual ~MachinePartCode();
			void Shutdown();
		private:
			void UpdateCode();
			void FindAudioController();
	};
}
#endif