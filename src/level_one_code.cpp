#include "level_one_code.hpp"

using namespace Azo;

LevelOneCode::LevelOneCode(engine::GameObject &game_object){
	this->game_object = &game_object;
	GetParents();
	FindAudioController();
}

void LevelOneCode::Shutdown(){
	for(auto obstacle : m_obstacle_list){
		obstacle = nullptr;
	}

	m_audio_controller = nullptr;

	m_player = nullptr;
}

void LevelOneCode::FindAudioController(){
	m_audio_controller = (game_object->GetAudioController(typeid(engine::AudioController)));
}

void LevelOneCode::GetParents(){
	for(auto parent : game_object->m_parent_list){
		if(parent->GetClassName() == "Player"){
			m_player = dynamic_cast<Player *>(parent);
		}else if(parent->GetClassName() == "Obstacle"){
			m_obstacle_list.push_back(dynamic_cast<Obstacle *>(parent));
		}
	}
}


void LevelOneCode::UpdateCode(){
	DEBUG("Position: " << game_object->m_current_position.first );
	//DEBUG("Collected parts: " << m_player->m_collected_parts);
	if(m_player->m_current_position.first >= 300.0f && game_object->m_current_position.first > -20198){
		game_object->m_current_position.first -= 4.0f;
		m_player->m_current_position.first = 299;
	}

	UpdateObstaclePosition();

	if(m_player->m_state != PlayerState::DIE){
		UpdatePhysics();
	}else{
		if(m_audio_controller->GetAudioState("tema_level_one") == engine::AudioState::PLAYING){
			m_audio_controller->StopAudio("tema_level_one");
		}else{
			// Nothing to do.
		}

		//TODO(Roger): Fix this KeyDownOnce method. Sometimes you need to press two times.
		if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){
			engine::Game::instance.ChangeScene("menu");
		}
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
}

void LevelOneCode::UpdatePhysics(){
	m_player->m_current_position.second += m_player->m_speed.second * engine::Game::instance.GetTimer().GetDeltaTime();
	double ground_y = 0.0f;
	if(m_player->m_speed.second < 0.0f && HasCeiling(&ground_y)){
		m_player->m_current_position.second = ground_y + 15;
		m_player->m_at_ceiling = true;
	}else if((m_player->m_speed.second >= 0.0f || m_player->m_state == PlayerState::SLIDE) && HasGround(&ground_y)){
		m_player->m_current_position.second = ground_y - m_player->m_half_size.second - m_player->m_half_size.second + 15;
		m_player->m_speed.second = m_player->M_ZERO_VECTOR.second;

		m_player->m_on_ground = true;

		m_player->m_center.first = m_player->m_current_position.first + m_player->m_half_size.first;
		m_player->m_center.second = m_player->m_current_position.second + m_player->m_half_size.second;

	}else{
		m_player->m_on_ground = false;
		m_player->m_at_ceiling = false;
	}

	//double delta_walked =  m_player->m_speed.first * engine::Game::instance.GetTimer().GetDeltaTime();
	double delta_walked =  m_player->m_speed.first;
	// DEBUG("Speed: " << m_player->m_speed.first);
	// DEBUG("Delta walked: " << delta_walked);

	m_player->m_current_position.first += delta_walked;

	double wall_x = 0.0;

	//Limiting player position on canvas.
	if(m_player->m_current_position.first >= 300 && game_object->m_current_position.first > -7390){
		m_player->m_current_position.first = 300;
	}

	if(m_player->m_speed.first > 0 &&
	   HasWallOnRight(&wall_x)){
		DEBUG("Collision with the wall");
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

	for(auto each_obstacle : m_obstacle_list){

		// If the obstacle is a machine part, we check the collision without invisible blocks (since it has animation).
		// If it collides, we return false (so the position isn't updated) and change the state of the machine part.
		// TODO(Roger): Update the collision methods so they return the colliding object.
		// TODO(Roger): Create states to the machine parts.

		if(each_obstacle->m_obstacle_type == ObstacleType::MACHINE_PART){
			std::pair<double, double> block_bottom_left = each_obstacle->CalcBottomLeft();
			std::pair<double, double> block_top_right = each_obstacle->CalcTopRight();

			double block_right = block_top_right.first;
			double block_left = block_bottom_left.first;
			double block_top = block_top_right.second;

			if(player_left <= block_right &&
			   player_right >= block_left &&
			   player_bottom > block_top &&
			   player_top < block_top){

				// Collided.
				each_obstacle->m_machine_part_state = MachinePartState::COLLECTED;
				m_player->m_collected_parts++;
				m_obstacle_list.remove(each_obstacle);

				return false;
			}
		}else{
			for(auto each_block : each_obstacle->m_block_list){
				std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
				std::pair<double, double> block_top_right = each_block->CalcTopRight();

				double block_right = block_top_right.first;
				double block_left = block_bottom_left.first;
				double block_top = block_top_right.second;

				if(player_left <= block_right &&
				   player_right >= block_left &&
				   player_bottom > block_top &&
				   player_top < block_top){

					*ground_y = block_top;

					if(each_obstacle->m_obstacle_type == ObstacleType::WESTERN_ROCK ||
					   each_obstacle->m_obstacle_type == ObstacleType::WESTERN_SPIKE){
						m_player->m_state = PlayerState::DIE;
					}

					return true;
				}
			}
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

		if(each_obstacle->m_obstacle_type == ObstacleType::MACHINE_PART){
			std::pair<double, double> block_bottom_left = each_obstacle->CalcBottomLeft();
			std::pair<double, double> block_top_right = each_obstacle->CalcTopRight();

			// These magic numbers are used because the walls must be a bit at the front of the top.
			double block_right = block_top_right.first + 5;
			double block_left = block_bottom_left.first - 5;
			double block_top = block_top_right.second + 16;
			double block_bottom = block_bottom_left.second - 16;



			if(player_left < block_left &&
			   player_left < block_right &&
			   player_top <= block_bottom &&
			   player_bottom >= block_top &&
			   player_right >= block_left){

				each_obstacle->m_machine_part_state = MachinePartState::COLLECTED;
				m_player->m_collected_parts++;
				m_obstacle_list.remove(each_obstacle);

				return false;
			}
		}else{

			for(auto each_block : each_obstacle->m_block_list){

				std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
				std::pair<double, double> block_top_right = each_block->CalcTopRight();

				// These magic numbers are used because the walls must be a bit at the front of the top.
				double block_right = block_top_right.first + 5;
				double block_left = block_bottom_left.first - 5;
				double block_top = block_top_right.second + 16;
				double block_bottom = block_bottom_left.second - 16;

				// DEBUG("Obstacle: " << each_obstacle->m_name);
				// DEBUG("Player left: " << player_left);
				// DEBUG("Player right: " << player_right);
				// DEBUG("Player top: " << player_top);
				// DEBUG("Player bottom: " << player_bottom);
				// DEBUG("Block left: " << block_left);
				// DEBUG("Block right: " << block_right);
				// DEBUG("Block top: " << block_top);
				// DEBUG("Block bottom: " << block_bottom);

				if(player_left < block_left &&
				   player_left < block_right &&
				   player_top <= block_bottom &&
				   player_bottom >= block_top &&
				   player_right >= block_left){

					*wall_x = block_left - 1.0f;
					return true;
				}

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
			double block_top = block_top_right.second;
			double block_bottom = block_bottom_left.second;


			if(player_left <= block_right &&
			   player_right > block_right &&
			   player_top <= block_bottom &&
			   player_bottom >= block_top){

				*wall_x = block_right + 1.0f;
				return true;
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
			double block_top = block_top_right.second;
			double block_bottom = block_bottom_left.second;

			if(player_left >= block_left &&
			   player_right <= block_right &&
			   player_top <= block_bottom &&
			   player_bottom >= block_top &&
			   player_top >= block_top){

				*ground_y = block_bottom;
				return true;
			}
		}
	}

	return false;

}
