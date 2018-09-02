	#ifndef MACHINE_PART_CODE
#define MACHINE_PART_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class obstacle;

	class machinePartCode : public engine::CodeComponent {
		private:
			obstacle *mMachinePart;
			engine::AudioController *mAudioController;
		public:
			machinePartCode(obstacle *machinePart);
			virtual ~machinePartCode();
			void shutDown();
		private:
			void updateCode();
			void findAudioController();
	};
}
#endif
