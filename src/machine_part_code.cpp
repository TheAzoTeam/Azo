#include "machine_part_code.hpp"
#include "obstacle.hpp"

using namespace Azo;

MachinePartCode::MachinePartCode(Obstacle *machine_part){
	m_machine_part = machine_part;
	FindAudioController();
}


void MachinePartCode::FindAudioController(){
	m_audio_controller = (m_machine_part->GetAudioController(typeid(engine::AudioController)));
}

void MachinePartCode::UpdateCode(){
	switch(m_machine_part->m_machine_part_state){
		case MachinePartState::COLLECTED:
			m_audio_controller->PlayAudio("coleta");

			m_machine_part->m_machine_part_state = MachinePartState::FINISHED;
			break;
		case MachinePartState::FINISHED:
			m_audio_controller->StopAudio("coleta");
			m_machine_part->m_object_state = engine::ObjectState::DISABLED;
		default:
			break;
	}
}