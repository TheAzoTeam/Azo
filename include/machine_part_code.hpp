#ifndef MACHINE_PART_CODE
#define MACHINE_PART_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class obstacle;

	class MachinePartCode : public engine::CodeComponent {
		private:
			obstacle *m_machine_part;
			engine::AudioController *mAudioController;
		public:
			MachinePartCode(obstacle *machine_part);
			virtual ~MachinePartCode();
			void shutDown();
		private:
			void updateCode();
			void findAudioController();
	};
}
#endif