#include "machine_part_code.hpp"
#include "obstacle.hpp"

using namespace Azo;

MachinePartCode::MachinePartCode(Obstacle *machine_part){
	m_machine_part = machine_part;
	findAudioController();
}

MachinePartCode::~MachinePartCode(){}

void MachinePartCode::Shutdown(){
	if(m_audio_controller != NULL){
		m_audio_controller = NULL;
	}
}

void MachinePartCode::findAudioController(){
	m_audio_controller = (m_machine_part->getAudioController(typeid(engine::AudioController)));
}

void MachinePartCode::updateCode(){
	switch(m_machine_part->mMachinePartState){
		case MachinePartState::COLLECTED:
			m_audio_controller->PlayAudio("coleta");

			m_machine_part->mMachinePartState = MachinePartState::FINISHED;
			break;
		case MachinePartState::FINISHED:
			m_machine_part->mObjectState = engine::ObjectState::DISABLED;
		default:
			break;
	}
}
