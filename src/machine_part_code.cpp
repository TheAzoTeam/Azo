#include "machine_part_code.hpp"
#include "obstacle.hpp"

using namespace Azo;

machinePartCode::machinePartCode(obstacle *machinePart) {
	mMachinePart = machinePart;
	findAudioController();
}

machinePartCode::~machinePartCode() {}

void machinePartCode::shutDown(){
	if (mAudioController != NULL) {
		mAudioController = NULL;
	}
}

void machinePartCode::findAudioController() {
	mAudioController = (mMachinePart->getAudioController(typeid(engine::AudioController)));
}

void machinePartCode::updateCode() {
	switch(mMachinePart->mMachinePartState) {
		case MachinePartState::COLLECTED:
			mAudioController->PlayAudio("coleta");

			mMachinePart->mMachinePartState = MachinePartState::FINISHED;
			break;
		case MachinePartState::FINISHED:
			mMachinePart->mObjectState = engine::ObjectState::DISABLED;
		default:
			break;
	}
}
