#include "player_code.hpp"
#include "game.hpp"
#include "player.hpp"

using namespace Azo;

PlayerCode::PlayerCode(){}

PlayerCode::~PlayerCode(){}

PlayerCode::PlayerCode(Player *player){
	m_player = player;
	m_player->mState = PlayerState::WALK;
	m_player->m_on_ground = true;
	FindAnimationController();
	FindAudioController();
}


void PlayerCode::FindAnimationController(){
	m_animation_controller = (m_player->GetAnimationController(typeid(engine::AnimationController)));
}

void PlayerCode::FindAudioController(){
	m_audio_controller = (m_player->GetAudioController(typeid(engine::AudioController)));
}

void PlayerCode::shutdown(){
	if(m_animation_controller != NULL){
		m_animation_controller = NULL;
	}
}


void PlayerCode::updateCode(){
	switch(m_player->mState){
		case PlayerState::WALK:

			m_animation_controller->StartUniqueAnimation("walking");

			if(m_player->m_pushes_right_wall || m_player->m_pushes_left_wall){
				//DEBUG("Update code method. Player Speed in X: " << m_player->m_speed.first);
				m_player->m_speed.first = m_player->M_ZERO_VECTOR.first;
			}else{
				m_player->m_speed.first = m_player->M_WALKING_SPEED;
				//DEBUG("PLAYER SHOULD HAVE SPEED! PLAYER SPEED " << m_player->m_speed.first);
			}

			if(engine::Game::instance.input_manager.KeyState(engine::Button::W)){
				//DEBUG("W pressed!");
				m_player->mState = PlayerState::JUMP;
				m_player->m_speed.second = m_player->M_JUMPING_SPEED; // Jumping speed.

			}else if(!m_player->m_on_ground){
				//DEBUG("Player isn't on ground. (WALK)");
				m_player->mState = PlayerState::JUMP;
			}

			if(engine::Game::instance.input_manager.KeyState(engine::Button::S)){
				m_player->mState = PlayerState::SLIDE;
			}

			break;

		case PlayerState::JUMP:

			if(m_player->m_on_ground){
				m_player->mState = PlayerState::WALK;
			}

			m_animation_controller->StartUniqueAnimation("jumping");

			m_player->m_speed.second += (m_player->M_GRAVITY * engine::Game::instance.GetTimer().GetDeltaTime());
			//DEBUG("updateCode method. Player Speed in Y: " << m_player->m_speed.second);

			if(m_player->m_pushes_right_wall){
				m_player->m_speed.first = m_player->M_ZERO_VECTOR.first;
			}else{
				m_player->m_speed.first = m_player->M_WALKING_SPEED;         // Walking speed.
			}

			// if(m_player->m_pushes_left_wall){
			//      m_player->m_speed.first = m_player->M_ZERO_VECTOR.first;
			// }

			break;

		case PlayerState::SLIDE:
			m_animation_controller->StartUniqueAnimation("sliding");

			if(m_animation_controller->GetAnimationStatus("sliding") == engine::AnimationState::FINISHED){
				m_player->mState = PlayerState::WALK;
				break;
			}

			m_player->m_speed.second += (m_player->M_GRAVITY * engine::Game::instance.GetTimer().GetDeltaTime());
			//DEBUG("Player speed: " << m_player->m_speed.second);

			if(m_player->m_pushes_right_wall){
				m_player->m_speed.first = m_player->M_ZERO_VECTOR.first;
				//TODO(Roger): Change this state to DEATH.
				m_player->mState = PlayerState::WALK;
			}

			if(engine::Game::instance.input_manager.KeyState(engine::Button::W)){
				m_player->mState = PlayerState::JUMP;
				m_player->m_speed.second = m_player->M_JUMPING_SPEED;
			}

			break;
		case PlayerState::DIE:
			m_animation_controller->StartUniqueAnimation("dying");

			m_audio_controller->PlayAudio("lost");

			break;
		case PlayerState::END:
			if(m_player->m_collected_parts < m_player->M_TOTAL_PARTS){
				m_animation_controller->StartUniqueAnimation("losing");

				if(m_animation_controller->GetAnimationStatus("losing") == engine::AnimationState::FINISHED){
					m_audio_controller->PlayAudio("lost");
				}
			}else{
				m_animation_controller->StartUniqueAnimation("victory");
				m_audio_controller->PlayAudio("victory");
			}

			break;
	}
}

