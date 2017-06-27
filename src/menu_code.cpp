#include "game.hpp"
#include "menu_code.hpp"

using namespace Azo;

MenuCode::MenuCode(engine::GameObject *game_object){
	this->game_object = game_object;
	FindAudioController();
}

void MenuCode::FindAudioController(){
	m_audio_controller = (game_object->GetAudioController(typeid(engine::AudioController)));
}

void MenuCode::UpdateCode(){
	if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){
		m_audio_controller->StopAudio("menu_theme");
		engine::Game::instance.ChangeScene("level_one");
	}

	if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::SPACE)){
		if(m_audio_controller->GetAudioState("menu_theme") == engine::AudioState::PLAYING){}
	}
}
