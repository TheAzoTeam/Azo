#include "game.hpp"
#include "menu_code.hpp"

using namespace Azo;

MenuCode::MenuCode(engine::GameObject *gameObject){
	this->gameObject = gameObject;
	FindAudioController();
	FindAnimationController();
}

void MenuCode::FindAnimationController(){
	m_animation_controller = (gameObject->GetAnimationController(typeid(engine::AnimationController)));
}

void MenuCode::FindAudioController(){
	m_audio_controller = (gameObject->GetAudioController(typeid(engine::AudioController)));
}

void MenuCode::UpdateCode(){
	if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){

		switch(m_current_button){
			case 1:
				m_audio_controller->StopAudio("menu_theme");
				engine::Game::instance.ChangeScene("level_one");
				break;
			case 2:
				engine::Game::instance.game_state = engine::GameState::EXIT;
				break;
			case 3:

				if(m_audio_controller->GetAudioState("menu_theme") == engine::AudioState::PLAYING){
					m_audio_controller->PauseAudio("menu_theme");
					m_animation_controller->StopAnimation("sound_enabled_button");
					m_animation_controller->StartAnimation("sound_disabled_button");
				}else{
					m_audio_controller->PlayAudio("menu_theme");
					m_animation_controller->StartAnimation("sound_enabled_button");
					m_animation_controller->StopAnimation("sound_disabled_button");
				}

				break;

		}
	}

	ChangeOption();
}

void MenuCode::ChangeOption(){

	switch(m_current_button){
		// Start Option.
		case 1:
			DEBUG("Start Button is selected.");

			m_animation_controller->StartAnimation("arrow_start");


			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::RIGHT_ARROW)){
				m_animation_controller->StopAnimation("arrow_start");

				m_current_button = 2;

			}

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::LEFT_ARROW)){
				m_animation_controller->StopAnimation("arrow_start");
				m_current_button = 3;
			}

			break;
		// Exit Option.
		case 2:
			DEBUG("Exit Button is selected.");


			m_animation_controller->StartAnimation("arrow_exit");

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::RIGHT_ARROW)){
				m_animation_controller->StopAnimation("arrow_exit");

				m_current_button = 3;
			}

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::LEFT_ARROW)){
				m_animation_controller->StopAnimation("arrow_exit");

				m_current_button = 1;
			}

			break;
		// Sound Option.
		case 3:
			DEBUG("Sound Button is selected.");

			m_animation_controller->StartAnimation("arrow_sound");

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::RIGHT_ARROW)){
				m_animation_controller->StopAnimation("arrow_sound");

				// Go back to the first option.
				m_current_button = 1;

			}

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::LEFT_ARROW)){
				m_animation_controller->StopAnimation("arrow_sound");

				m_current_button = 2;
			}

			break;
	}
}

