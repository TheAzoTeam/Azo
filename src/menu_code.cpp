#include "menu_code.hpp"
#include "game.hpp"

using namespace Azo;

MenuCode::MenuCode(){}

MenuCode::MenuCode(engine::GameObject &game_object){
	this->game_object = &game_object;
	FindAudioController();
}

MenuCode::~MenuCode(){}

void MenuCode::FindAudioController(){
	this->audio_controller = (game_object->GetAudioController(typeid(engine::AudioController)));
}

bool MenuCode::UpdateCode(){
	NextScene();
	DisableSound();
	return true;
}

void MenuCode::NextScene(){
	if(engine::Game::instance.input_manager.KeyDown(engine::Button::ENTER)){
		DEBUG("Enter pressionado!");
		engine::Game::instance.ChangeScene(global::player_scene);
	}
}

void MenuCode::DisableSound(){
	ASSERT(audio_controller != NULL, "AudioController can't be null while disabling sound.");

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