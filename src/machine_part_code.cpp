#include "machine_part_code.hpp"
#include "obstacle.hpp"

using namespace Azo;

MachinePartCode::MachinePartCode(Obstacle *machine_part){
	m_machine_part = machine_part;
	FindAudioController();
}

MachinePartCode::~MachinePartCode(){}

void MachinePartCode::Shutdown(){
	if(mAudioController != NULL){
		mAudioController = NULL;
	}
}

void MachinePartCode::FindAudioController(){
	mAudioController = (m_machine_part->GetAudioController(typeid(engine::AudioController)));
}

void MachinePartCode::UpdateCode(){
	switch(m_machine_part->m_machine_part_state){
		case MachinePartState::COLLECTED:
			mAudioController->PlayAudio("coleta");

			m_machine_part->m_machine_part_state = MachinePartState::FINISHED;
			break;
		case MachinePartState::FINISHED:
			m_machine_part->m_object_state = engine::ObjectState::DISABLED;
		default:
			break;
	}
}
