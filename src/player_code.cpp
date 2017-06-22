#include "player_code.hpp"
#include "game.hpp"
#include "player.hpp"

using namespace Azo;

PlayerCode::PlayerCode(){}

PlayerCode::PlayerCode(engine::GameObject &game_object){
	m_player = dynamic_cast<Player *>(&game_object);
	m_player->m_state = PlayerState::STAND;
	m_player->m_on_ground = true;
	FindAnimationController();
}

void PlayerCode::FindAnimationController(){
	DEBUG("PlayerCode::FindAnimationController method.");
	m_animation_controller = (m_player->GetAnimationController(typeid(engine::AnimationController)));
}

void PlayerCode::UpdateCode(){
	DEBUG("Updating Player Code.");
}