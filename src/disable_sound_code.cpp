#include "disable_sound_code.hpp"

using namespace Azo;

DisableSoundCode::DisableSoundCode(){}

DisableSoundCode::DisableSoundCode(engine::GameObject &game_object){
	DEBUG("Disable sound constructor");
	this->game_object = &game_object;
	this->component_state = engine::State::ENABLED;
	FindAudioController();
}

void DisableSoundCode::FindAudioController(){
	this->audio_controller = (game_object->GetAudioController(typeid(engine::AudioController)));
}

void DisableSoundCode::UpdateCode(){
	if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::SPACE)){
		if(audio_controller->GetAudioState("menu_theme") == engine::AudioState::PLAYING){
			DEBUG("Stopping Audio");
			audio_controller->StopAudio("menu_theme");
		}else{
			DEBUG("Starting Audio");
			audio_controller->PlayAudio("menu_theme");
		}
	}
}