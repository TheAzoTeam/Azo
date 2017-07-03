#include "level_one_code.hpp"

using namespace Azo;

LevelOneCode::LevelOneCode(engine::GameObject &game_object){
	this->game_object = &game_object;
	GetParents();
}

void LevelOneCode::GetParents(){
	for(auto parent : game_object->m_parent_list){
		if(parent->GetClassName() == "Player"){
			m_player = dynamic_cast<Player *>(parent);
		}else if(parent->GetClassName() == "Obstacle"){
			if(parent->m_name != "ground"){
				m_obstacle_list.push_back(dynamic_cast<Obstacle *>(parent));
			}else{
				m_ground = dynamic_cast<Obstacle *>(parent);
			}
		}else if(parent->GetClassName() == "MachinePart"){
			m_machine_part_list.push_back(dynamic_cast<MachinePart *>(parent));
		}
	}
}


void LevelOneCode::UpdateCode(){
	if(m_player->m_current_position.first >= 300.0f){
		game_object->m_current_position.first -= 4.0f;
		m_player->m_current_position.first = 299;
	}

	UpdateObstaclePosition();
	UpdateMachinePartPosition();

	if(m_player->m_state != PlayerState::DIE){
		UpdatePhysics();
	}
}

void LevelOneCode::UpdateObstaclePosition(){
	for(auto each_obstacle : m_obstacle_list){
		each_obstacle->m_current_position.first = game_object->m_current_position.first + each_obstacle->m_position_relative_to_parent.first;
		each_obstacle->m_current_position.second = game_object->m_current_position.second + each_obstacle->m_position_relative_to_parent.second;

		for(auto block : each_obstacle->m_block_list){
			block->m_current_position.first = game_object->m_current_position.first + block->m_position_relative_to_parent.first;
			block->m_current_position.second = game_object->m_current_position.second + block->m_position_relative_to_parent.second;

			block->m_center.first = block->m_current_position.first + block->m_half_size.first;
			block->m_center.second = block->m_current_position.second + block->m_half_size.second;

			// DEBUG("BLock current position in X: " << block->m_current_position.first);
			// DEBUG("BLock current position in Y: " << block->m_current_position.second);
			// DEBUG("Block center in X: " << block->m_center.first);
			// DEBUG("Block center in Y: " << block->m_center.second);

		}
	}

	for(auto block : m_ground->m_block_list){
		block->m_current_position.first = game_object->m_current_position.first + block->m_position_relative_to_parent.first;
		block->m_current_position.second = game_object->m_current_position.second + block->m_position_relative_to_parent.second;

		block->m_center.first = block->m_current_position.first + block->m_half_size.first;
		block->m_center.second = block->m_current_position.second + block->m_half_size.second;
	}
}

void LevelOneCode::UpdateMachinePartPosition(){
	for(auto each_part : m_machine_part_list){
		each_part->m_current_position.first = game_object->m_current_position.first +
						      each_part->m_position_relative_to_parent.first;
		each_part->m_current_position.second = game_object->m_current_position.second +
						       each_part->m_position_relative_to_parent.second;
	}
}


void LevelOneCode::UpdatePhysics(){
	m_player->m_current_position.second += m_player->m_speed.second * engine::Game::instance.GetTimer().GetDeltaTime();
	double ground_y = 0.0f;
	if(m_player->m_speed.second < 0.0f && HasCeiling(&ground_y)){
		m_player->m_current_position.second = ground_y + 15;
		m_player->m_at_ceiling = true;
	}else if((m_player->m_speed.second >= 0.0f || m_player->m_state == PlayerState::SLIDE) && HasGround(&ground_y)){
		DEBUG("On ground!");
		m_player->m_current_position.second = ground_y - m_player->m_half_size.second - m_player->m_half_size.second + 15;
		m_player->m_speed.second = m_player->M_ZERO_VECTOR.second;

		m_player->m_on_ground = true;

		m_player->m_center.first = m_player->m_current_position.first + m_player->m_half_size.first;
		m_player->m_center.second = m_player->m_current_position.second + m_player->m_half_size.second;

		DEBUG("Player feet: " << m_player->m_center.second + m_player->m_half_size.second);

	}else{
		m_player->m_on_ground = false;
		m_player->m_at_ceiling = false;
	}

	double delta_walked =  m_player->m_speed.first * engine::Game::instance.GetTimer().GetDeltaTime();
	m_player->m_current_position.first += delta_walked;

	double wall_x = 0.0;

	//Limiting player position on canvas.
	if(m_player->m_current_position.first >= 300 && game_object->m_current_position.first > -7390){
		m_player->m_current_position.first = 300;
	}

	if(m_player->m_speed.first > 0 &&
	   HasWallOnRight(&wall_x)){
		DEBUG("Collision with the wall");
		//DEBUG("Wall x: " << wall_x);
		m_player->m_current_position.first = wall_x - (m_player->m_half_size.first * 2);
		m_player->m_pushes_left_wall = true;
		m_player->m_state = PlayerState::DIE;
	}else{
		m_player->m_pushes_left_wall = false;
	}

	if(m_player->m_speed.first < 0.0f &&
	   HasWallOnLeft(&wall_x)){
		m_player->m_state = PlayerState::DIE;
	}else{
		m_player->m_pushes_right_wall = false;
	}
}

bool LevelOneCode::HasGround(double *ground_y){
	std::pair<double, double> player_bottom_left = m_player->CalcBottomLeft();
	std::pair<double, double> player_top_right = m_player->CalcTopRight();

	double player_top = player_top_right.second;
	double player_bottom = player_bottom_left.second;
	double player_left = player_bottom_left.first;
	double player_right = player_top_right.first;

	// First, we check the collision with the level's ground. If it's true, then we return
	// true imediatly. The ground's top is calculated at the CheckCollisionWithLevelGround method.
	bool collision_with_level_ground = CheckCollisionWithLevelGround(player_top,
									 player_bottom,
									 player_left, player_right, ground_y);

	if(collision_with_level_ground){
		return true;
	}else{
		DEBUG("Isn't colliding with the level ground.");
	}

	for(auto each_obstacle : m_obstacle_list){

		for(auto each_block : each_obstacle->m_block_list){
			std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
			std::pair<double, double> block_top_right = each_block->CalcTopRight();

			double block_right = block_top_right.first;
			double block_left = block_bottom_left.first;
			double block_top = block_top_right.second;

			// DEBUG("Player left: " << player_left);
			// DEBUG("Block left: " << block_left);
			// DEBUG("Block right: " << block_right);
			// DEBUG("Player right: " << player_right);
			// DEBUG("Block top: " << block_top);
			// DEBUG("Player top: " << player_top);
			// DEBUG("Player bottom: " << player_bottom);

			if(player_left <= block_right && player_right >= block_left){

				if(player_bottom < block_top){
					return false;
				}

				if(player_top > block_top){
					return false;
				}

				*ground_y = block_top;

				if(each_obstacle->m_obstacle_type == ObstacleType::WESTERN_ROCK){
					m_player->m_state = PlayerState::DIE;
				}

				return true;
			}
		}
	}

	return false;
}

bool LevelOneCode::CheckCollisionWithLevelGround(double player_top,
						 double player_bottom,
						 double player_left,
						 double player_right, double *ground_y){

	for(auto each_block : m_ground->m_block_list){
		std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
		std::pair<double, double> block_top_right = each_block->CalcTopRight();

		double block_right = block_top_right.first;
		double block_left = block_bottom_left.first;
		double block_top = block_top_right.second;

		DEBUG("Player left: " << player_left);
		DEBUG("Block left: " << block_left);
		DEBUG("Block right: " << block_right);
		DEBUG("Player right: " << player_right);
		DEBUG("Block top: " << block_top);
		DEBUG("Player top: " << player_top);
		DEBUG("Player bottom: " << player_bottom);

		if(player_left <= block_right && player_right >= block_left){

			if(player_bottom < block_top){
				return false;
			}

			if(player_top > block_top){
				return false;
			}

			*ground_y = block_top;

			return true;
		}
	}

	return false;
}

bool LevelOneCode::HasWallOnRight(double *wall_x){
	std::pair<double, double> player_bottom_left = m_player->CalcBottomLeft();
	std::pair<double, double> player_top_right = m_player->CalcTopRight();

	double player_top = player_top_right.second;
	double player_bottom = player_bottom_left.second;
	double player_left = player_bottom_left.first;
	double player_right = player_top_right.first;

	for(auto each_obstacle : m_obstacle_list){

		for(auto each_block : each_obstacle->m_block_list){

			std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
			std::pair<double, double> block_top_right = each_block->CalcTopRight();

			// These magic numbers are used because the walls must be a bit at the front of the top.
			double block_right = block_top_right.first + 5;
			double block_left = block_bottom_left.first - 5;
			double block_top = block_top_right.second + 16;
			double block_bottom = block_bottom_left.second - 16;

			// DEBUG("Player left: " << player_left);
			// DEBUG("Block left: " << block_left);
			// DEBUG("Block right: " << block_right);
			// DEBUG("Player bottom: " << player_bottom);
			// DEBUG("Block top: " << block_top);
			//
			if(player_left < block_left && player_left < block_right){
				//
				// DEBUG("Player top: " << player_top);
				// DEBUG("Block bottom: " << block_bottom);
				// DEBUG("Player right: " << player_right);
				// DEBUG("Block left: " << block_left);

				if(player_top > block_bottom){
					return false;
				}

				if(player_bottom < block_top){
					return false;
				}

				if(player_right < block_left - 1){
					return false;
				}

				*wall_x = block_left - 1.0f;
				return true;
			}
		}
	}

	return false;
}

bool LevelOneCode::HasWallOnLeft(double *wall_x){
	std::pair<double, double> player_bottom_left = m_player->CalcBottomLeft();
	std::pair<double, double> player_top_right = m_player->CalcTopRight();

	double player_top = player_top_right.second;
	double player_bottom = player_bottom_left.second;
	double player_left = player_bottom_left.first;
	double player_right = player_top_right.first;

	for(auto each_obstacle : m_obstacle_list){

		for(auto each_block : each_obstacle->m_block_list){

			std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
			std::pair<double, double> block_top_right = each_block->CalcTopRight();

			double block_right = block_top_right.first;

			// DEBUG("Block right: " << block_right);
			// DEBUG("Player top: " << player_top);
			// DEBUG("Player bottom: " << player_bottom);
			// DEBUG("Player right: " << player_right);
			// DEBUG("Block right: " << block_right);

			if(player_left <= block_right && player_right > block_right){

				double block_top = block_top_right.second;
				double block_bottom = block_bottom_left.second;


				if(player_top > block_bottom){
					return false;
				}

				if(player_bottom < block_top){
					return false;
				}

				if(player_right > block_right + 1){
					*wall_x = block_right + 1.0f;
					return true;
				}
			}

		}
	}

	return false;
}

bool LevelOneCode::HasCeiling(double *ground_y){
	std::pair<double, double> player_bottom_left = m_player->CalcBottomLeft();
	std::pair<double, double> player_top_right = m_player->CalcTopRight();

	double player_top = player_top_right.second;
	double player_bottom = player_bottom_left.second;
	double player_left = player_bottom_left.first;
	double player_right = player_top_right.first;


	for(auto each_obstacle : m_obstacle_list){

		for(auto each_block : each_obstacle->m_block_list){
			std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
			std::pair<double, double> block_top_right = each_block->CalcTopRight();

			double block_left = block_bottom_left.first;
			double block_right = block_top_right.first;

			if(player_left >= block_left && player_right <= block_right){

				double block_top = block_top_right.second;
				double block_bottom = block_bottom_left.second;
				//
				// DEBUG("Player top: " << player_top);
				// DEBUG("Player bottom: " << player_bottom);
				// DEBUG("Block top: " << block_top);
				// DEBUG("Block_bottom: " << block_bottom);

				if(player_top > block_bottom){
					return false;
				}

				if(player_bottom < block_top){
					return false;
				}

				if(player_top < block_bottom && player_top > block_top){
					*ground_y = block_bottom;
					return true;
				}
			}
		}
	}

	return false;

}
