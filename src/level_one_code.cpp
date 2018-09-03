#include "level_one_code.hpp"

using namespace Azo;

LevelOneCode::LevelOneCode(engine::GameObject &gameObject){
	this->gameObject = &gameObject;
	GetParents();
	FindAudioController();
}

void LevelOneCode::shutdown(){
	for(auto obstacle : m_obstacle_list){
		obstacle = nullptr;
	}

	m_audio_controller = nullptr;

	m_player = nullptr;
}

void LevelOneCode::FindAudioController(){
	m_audio_controller = (gameObject->GetAudioController(typeid(engine::AudioController)));
}

void LevelOneCode::GetParents(){
	for(auto parent : gameObject->m_parent_list){
		if(parent->getClassName() == "Player"){
			m_player = dynamic_cast<Player *>(parent);
		}else if(parent->getClassName() == "Obstacle"){
			m_obstacle_list.push_back(dynamic_cast<Obstacle *>(parent));
		}else if(parent->mName == "winning_screen"){
			m_winning_screen = parent;
		}else if(parent->mName == "losing_parts"){
			m_losing_parts = parent;
		}else if(parent->mName == "losing_death"){
			m_losing_death = parent;
		}else if(parent->mName == "arrow"){
			m_arrow = parent;
		}

	}
}


void LevelOneCode::updateCode(){
	//DEBUG("Position: " << gameObject->mCurrentPosition.first );
	//DEBUG("Collected parts: " << m_player->m_collected_parts);
	if(m_player->mCurrentPosition.first >= 300.0f && gameObject->mCurrentPosition.first > -17600){
		gameObject->mCurrentPosition.first -= 4.0f;
		m_player->mCurrentPosition.first = 299;
	}else if(m_player->mCurrentPosition.first >= 300.0f){
		m_waiting_time += engine::Game::instance.GetTimer().GetDeltaTime();
		m_player->m_speed.first = 0;
		m_audio_controller->StopAudio("tema_level_one");
		m_player->mState = PlayerState::END;

		if(m_player->m_collected_parts != m_player->M_TOTAL_PARTS && m_waiting_time >= 10000.0f){
			m_losing_parts->mObjectState = engine::ObjectState::ENABLED;
			ChangeOption();

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){
				ChooseOption();
			}

		}else if(m_player->m_collected_parts == m_player->M_TOTAL_PARTS && m_waiting_time >= 5000.0f){
			m_winning_screen->mObjectState = engine::ObjectState::ENABLED;
			ChangeOption();

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){
				ChooseOption();
			}
		}

	}

	UpdateObstaclePosition();

	if(m_player->mState != PlayerState::DIE){
		UpdatePhysics();
	}else{
		m_waiting_time += engine::Game::instance.GetTimer().GetDeltaTime();

		if(m_waiting_time >= 2300.0f){
			m_losing_death->mObjectState = engine::ObjectState::ENABLED;
			ChangeOption();
			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){
				ChooseOption();
			}
		}

		if(m_audio_controller->GetAudioState("tema_level_one") == engine::AudioState::PLAYING){
			m_audio_controller->StopAudio("tema_level_one");
		}else{
			// Nothing to do.
		}

	}
}

void LevelOneCode::ChangeOption(){
	switch(m_current_option){
		case 1:
			m_arrow->mObjectState = engine::ObjectState::ENABLED;

			m_arrow->mCurrentPosition = std::make_pair(70, 260);

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::RIGHT_ARROW)){
				m_current_option = 2;
			}

			break;
		case 2:

			m_arrow->mCurrentPosition = std::make_pair(515, 260);

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::LEFT_ARROW)){
				m_current_option = 1;
			}

			break;
	}
}

void LevelOneCode::ChooseOption(){
	switch(m_current_option){
		case 1:
			m_audio_controller->StopAllAudios();
			engine::Game::instance.ChangeScene("level_one");
			break;
		case 2:
			engine::Game::instance.ChangeScene("menu");
			break;
	}
}



void LevelOneCode::UpdateObstaclePosition(){
	for(auto each_obstacle : m_obstacle_list){
		each_obstacle->mCurrentPosition.first = gameObject->mCurrentPosition.first + each_obstacle->m_position_relative_to_parent.first;
		each_obstacle->mCurrentPosition.second = gameObject->mCurrentPosition.second + each_obstacle->m_position_relative_to_parent.second;

		for(auto block : each_obstacle->m_block_list){
			block->mCurrentPosition.first = gameObject->mCurrentPosition.first + block->m_position_relative_to_parent.first;
			block->mCurrentPosition.second = gameObject->mCurrentPosition.second + block->m_position_relative_to_parent.second;

			block->mCenter.first = block->mCurrentPosition.first + block->mHalfSize.first;
			block->mCenter.second = block->mCurrentPosition.second + block->mHalfSize.second;

			// DEBUG("BLock current position in X: " << block->mCurrentPosition.first);
			// DEBUG("BLock current position in Y: " << block->mCurrentPosition.second);
			// DEBUG("Block center in X: " << block->mCenter.first);
			// DEBUG("Block center in Y: " << block->mCenter.second);

		}
	}
}

void LevelOneCode::UpdatePhysics(){
	m_player->mCurrentPosition.second += m_player->m_speed.second * engine::Game::instance.GetTimer().GetDeltaTime();
	double ground_y = 0.0f;
	if(m_player->m_speed.second < 0.0f && HasCeiling(&ground_y)){
		m_player->mCurrentPosition.second = ground_y + 15;
		m_player->m_at_ceiling = true;
	}else if((m_player->m_speed.second >= 0.0f || m_player->mState == PlayerState::SLIDE) && HasGround(&ground_y)){
		m_player->mCurrentPosition.second = ground_y - m_player->mHalfSize.second - m_player->mHalfSize.second + 15;
		m_player->m_speed.second = m_player->M_ZERO_VECTOR.second;

		m_player->m_on_ground = true;

		m_player->mCenter.first = m_player->mCurrentPosition.first + m_player->mHalfSize.first;
		m_player->mCenter.second = m_player->mCurrentPosition.second + m_player->mHalfSize.second;

	}else{
		m_player->m_on_ground = false;
		m_player->m_at_ceiling = false;
	}

	//double delta_walked =  m_player->m_speed.first * engine::Game::instance.GetTimer().GetDeltaTime();
	double delta_walked =  m_player->m_speed.first;
	// DEBUG("Speed: " << m_player->m_speed.first);
	// DEBUG("Delta walked: " << delta_walked);

	m_player->mCurrentPosition.first += delta_walked;

	double wall_x = 0.0;

	//Limiting player position on canvas.
	if(m_player->mCurrentPosition.first >= 300 && gameObject->mCurrentPosition.first > -7390){
		m_player->mCurrentPosition.first = 300;
	}

	if(m_player->m_speed.first > 0 &&
	   HasWallOnRight(&wall_x)){
		DEBUG("Collision with the wall");
		m_player->mCurrentPosition.first = wall_x - (m_player->mHalfSize.first * 2);
		m_player->m_pushes_left_wall = true;
		m_player->mState = PlayerState::DIE;
	}else{
		m_player->m_pushes_left_wall = false;
	}

	if(m_player->m_speed.first < 0.0f &&
	   HasWallOnLeft(&wall_x)){
		m_player->mState = PlayerState::DIE;
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

				// DEBUG("Obstacle: " << each_obstacle->mName);
				// DEBUG("Player left: " << player_left);
				// DEBUG("Player right: " << player_right);
				// DEBUG("Player top: " << player_top);
				// DEBUG("Player bottom: " << player_bottom);
				// DEBUG("Block left: " << block_left);
				// DEBUG("Block right: " << block_right);
				// DEBUG("Block top: " << block_top);

				if(player_left <= block_right &&
				   player_right >= block_left &&
				   player_bottom > block_top &&
				   player_top < block_top){

					*ground_y = block_top;

					if(each_obstacle->m_obstacle_type == ObstacleType::WESTERN_ROCK ||
					   each_obstacle->m_obstacle_type == ObstacleType::WESTERN_SPIKE ||
					   each_obstacle->m_obstacle_type == ObstacleType::WESTERN_POST){
						m_player->mState = PlayerState::DIE;
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

				// DEBUG("Obstacle: " << each_obstacle->mName);
				// DEBUG("Game object position x: " << gameObject->mCurrentPosition.first);
				// DEBUG("Game object position y: " << gameObject->mCurrentPosition.second);
				//
				// DEBUG("Obstacle position x: " << each_obstacle->mCurrentPosition.first);
				// DEBUG("Obstacle position y: " << each_obstacle->mCurrentPosition.second);
				//
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

					if(each_obstacle->m_obstacle_type == ObstacleType::WESTERN_POST){
						m_player->mState = PlayerState::DIE;
					}

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

				if(each_obstacle->m_obstacle_type == ObstacleType::WESTERN_POST){
					m_player->mState = PlayerState::DIE;
				}

				*ground_y = block_bottom;
				return true;
			}
		}
	}

	return false;

}
