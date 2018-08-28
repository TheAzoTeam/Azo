#include "machine_part_code.hpp"
#include "obstacle.hpp"

using namespace Azo;

MachinePartCode::MachinePartCode(obstacle *machine_part){
	m_machine_part = machine_part;
	findAudioController();
}

MachinePartCode::~MachinePartCode(){}

void MachinePartCode::shutDown(){
	if(mAudioController != NULL){
		mAudioController = NULL;
	}
}

void MachinePartCode::findAudioController(){
	mAudioController = (m_machine_part->getAudioController(typeid(engine::AudioController)));
}

void MachinePartCode::updateCode(){
	switch(m_machine_part->mMachinePartState){
		case MachinePartState::COLLECTED:
			mAudioController->PlayAudio("coleta");

			m_machine_part->mMachinePartState = MachinePartState::FINISHED;
			break;
		case MachinePartState::FINISHED:
			m_machine_part->mObjectState = engine::ObjectState::DISABLED;
		default:
			break;
	}
}
