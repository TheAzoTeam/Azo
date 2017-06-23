#include "level_one_code.hpp"

using namespace Azo;

LevelOneCode::LevelOneCode(engine::GameObject &game_object){
	this->game_object = &game_object;
	GetParents();
}

void LevelOneCode::GetParents(){
	DEBUG("Parent list size: " << game_object->m_parent_list.size());
	for(auto parent : game_object->m_parent_list){
		if(parent->GetClassName() == "Player"){
			m_player = dynamic_cast<Player *>(parent);
		}
	}
}


void LevelOneCode::UpdateCode(){
	DEBUG("Updating LeveOne Code.");
	if(m_player->m_current_position.first >= 300.0f){
		game_object->m_current_position.first -= 2.0f;
		m_player->m_current_position.first = 299;
	}
}